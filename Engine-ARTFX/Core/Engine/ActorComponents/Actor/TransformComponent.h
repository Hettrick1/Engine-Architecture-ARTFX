#pragma once

#include "Vector3D.h"
#include "Quaternion.h"
#include "Matrix4D.h"
#include "Matrix4DRow.h"
#include "Maths.h"

class Actor;

class TransformComponent
{
public:
	TransformComponent(Actor* pOwner, Vector3D position, Vector3D size, Quaternion rotation);
	TransformComponent();

	Vector3D GetPosition();
	Vector3D GetSize();
	Quaternion GetRotation();
	Matrix4DRow GetWorldTransform();

	void SetPosition(Vector3D newPosition);
	void SetSize(Vector3D newSize);
	void SetRotation(Quaternion newRotation);
	void SetOwner(Actor* pOwner);

	void RotateX(float pAngle);
	void RotateY(float pAngle);
	void RotateZ(float pAngle);

	Vector3D Right() const { return Vector3D::Transform(Vector3D::unitY, mRotation); } // pas sur que ce soit Y donc inverser avec le z si ca fait de la merde
	Vector3D Up() const { return Vector3D::Transform(Vector3D::unitZ, mRotation); }
	Vector3D Forward() const { return Vector3D::Transform(Vector3D::unitX, mRotation); }

	void ComputeWorldTransform();

private:
	Vector3D mPosition;
	Vector3D mSize;
	Quaternion mRotation;
	Matrix4DRow mWorldTransform;
	Actor* mOwner;
	bool mNeedsToUpdate;
};

