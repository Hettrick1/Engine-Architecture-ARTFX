#pragma once
#include <cmath>
#include <string>
#include "Vector2D.h"

struct Vector3D
{
	float x, y, z;

	Vector3D() :x(0), y(0), z(0){}
	Vector3D(float pX, float pY, float pZ) : x(pX), y(pY), z(pZ) {}
	Vector3D(float size) : x(size), y(size), z(size) {}

	static const Vector3D Zero, One, Forward, Up, Right;

	//--------------------Operators overload--------------------

	//operators +=, -=, *=, /= with vector 3
	inline void operator += (Vector3D& right) {
		x += right.x;
		y += right.y;
		z += right.z;
	}
	inline void operator -= (Vector3D& right) {
		x -= right.x;
		y -= right.y;
		z -= right.z;
	}
	inline void operator *= (float scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
	}
	inline void operator /= (float scalar) {
		x /= scalar;
		y /= scalar;
		z /= scalar;
	}
	inline void operator = (float scalar) {
		x = scalar;
		y = scalar;
		z = scalar;
	}

	//operators +=, -= with vector 2
	inline void operator += (Vector2D& right) {
		x += right.x;
		y += right.y;
	}
	inline void operator -= (Vector2D& right) {
		x -= right.x;
		y -= right.y;
	}

	//operators +, - with vector 3
	friend Vector3D operator + (Vector3D& left, Vector3D& right) {
		return { left.x + right.x, left.y + right.y, left.z + right.z };
	}
	friend Vector3D operator - (Vector3D& left, Vector3D& right) {
		return { left.x - right.x, left.y - right.y, left.z - right.z };
	}

	//operators +, - with vector 2
	friend Vector3D operator + (Vector2D& left, Vector3D& right) {
		return { left.x + right.x, left.y + right.y, right.z };
	}
	friend Vector3D operator + (Vector3D& left, Vector2D& right) {
		return { left.x + right.x, left.y + right.y, left.z};
	}

	friend Vector3D operator - (Vector2D& left, Vector3D& right) {
		return { left.x - right.x, left.y - right.y, right.z };
	}
	friend Vector3D operator - (Vector3D& left, Vector2D& right) {
		return { left.x - right.x, left.y - right.y, left.z};
	}

	//operators *, / with vector 3
	friend Vector3D operator * (Vector3D& left, float scalar) {
		return { left.x * scalar, left.y * scalar, left.z * scalar };
	}
	friend Vector3D operator * (float scalar, Vector3D& right) {
		return { scalar * right.x, scalar * right.y, scalar * right.z };
	}
	friend Vector3D operator / (Vector3D& left, float scalar) {
		return { left.x / scalar, left.y / scalar, left.z / scalar };
	}
	friend Vector3D operator / (float scalar, Vector3D& right) {
		return { scalar / right.x, scalar / right.y , scalar / right.z };
	}

	friend bool operator == (Vector3D& left, Vector3D& right) {
		if (left.x == right.x && left.y == right.y && left.z == right.z) {
			return true;
		}
		else {
			return false;
		}
	}
	friend bool operator != (Vector3D& left, Vector3D& right) {
		if (left.x == right.x && left.y == right.y && left.z == right.z) {
			return false;
		}
		else {
			return true;
		}
	}

	//--------------------Functions--------------------

	inline float Length() const { 
		float sum = (x * x) + (y * y) + (z * z);
		return sqrt(sum);
	}
	inline void Normalize() { 
		(*this) /= Length();
	}
	friend Vector3D Normalize(Vector3D temp) {
		return temp / temp.Length();
	}
	friend float Dot(Vector3D& left, Vector3D& right) {
		return left.x * right.x + left.y * right.y + left.z * right.z;
	}
	friend Vector3D CrossProduct(Vector3D& left, Vector3D& right) {
		return Vector3D(left.y * right.z - left.z * right.y, left.z * right.x - left.x * right.z, left.x * right.y - left.y * right.x);
	}
	inline Vector3D CrossProduct(Vector3D& right) {
		return Vector3D(y * right.z - z * right.y, z * right.x - x * right.z, x * right.y - y * right.x);
	}
	
	inline void Clamp(Vector3D& min, Vector3D& max) {
		if ((*this).x < min.x) (*this).x = min.x;
		if ((*this).x > max.x) (*this).x = max.x;

		if ((*this).y < min.y) (*this).y = min.y;
		if ((*this).y > max.y) (*this).y = max.y;

		if ((*this).z < min.z) (*this).z = min.z;
		if ((*this).z > max.z) (*this).z = max.z;
	}

	friend Vector3D Clamp(Vector3D temp, Vector3D& min, Vector3D& max) {
		if (temp.x < min.x) temp.x = min.x;
		if (temp.x > max.x) temp.x = max.x;

		if (temp.y < min.y) temp.y = min.y;
		if (temp.y > max.y) temp.y = max.y;

		if (temp.z < min.z) temp.z = min.z;
		if (temp.z > max.z) temp.z = max.z;

		return temp;
	}

	inline float Distance(Vector3D& vec) const {
		return sqrt(((*this).x - vec.x) * ((*this).x - vec.x) + ((*this).y - vec.y) * ((*this).y - vec.y) + ((*this).z - vec.z) * ((*this).z - vec.z));
	}

	inline bool Equals(Vector3D& right, float acceptance) {
		if (x < right.x - acceptance || x > right.y + acceptance || y < right.y - acceptance || y > right.y + acceptance || z < right.z - acceptance || z > right.z + acceptance) return true;
		else return false;
	}

	inline std::string ToString() {
		return "( " + std::to_string(x) + " , " + std::to_string(y) + " , " + std::to_string(z) + " )";
	}
};