#pragma once
#include <cmath>

struct Vector2D
{
	float x, y;

	Vector2D() :x(0), y(0) {}
	Vector2D(float pX, float pY): x(pX), y(pY){}

	static const Vector2D Zero, One;

	inline void operator += (Vector2D& right) {
		x += right.x;
		y += right.y;
	}
	inline void operator -= (Vector2D& right) {
		x -= right.x;
		y -= right.y;
	}
	inline void operator *= (float scalar) {
		x *= scalar;
		y *= scalar;
	}
	inline void operator /= (float scalar) {
		x /= scalar;
		y /= scalar;
	}
	friend Vector2D operator + (Vector2D& left, Vector2D& right) {
		return { left.x + right.x, left.y + right.y };
	}
	friend Vector2D operator - (Vector2D& left, Vector2D& right) {
		return { left.x - right.x, left.y - right.y };
	}
	friend Vector2D operator * (Vector2D& left, float scalar) {
		return { left.x * scalar, left.y * scalar };
	}
	friend Vector2D operator * (float scalar, Vector2D& right) {
		return { scalar * right.x, scalar * right.y };
	}
	friend Vector2D operator / (Vector2D& left, float scalar) {
		return { left.x / scalar, left.y / scalar };
	}
	friend Vector2D operator / (float scalar, Vector2D& right) {
		return { scalar / right.x, scalar / right.y };
	}

	inline float Lenght() const {
		float sum = x*x + y*y;
		return sqrt(sum);
	}
	inline void Normalize() {
		(*this) /= Lenght();
	}
	inline Vector2D Normalized() {
		return (*this) / Lenght();
	}
	friend float Dot(Vector2D& left, Vector2D& right) {
		return left.x * right.x + left.y * right.y;
	}

};

