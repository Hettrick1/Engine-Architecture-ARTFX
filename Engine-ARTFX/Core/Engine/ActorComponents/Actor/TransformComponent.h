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
	void Translate(Vector3D pTranslation);
	void SetSize(Vector3D newSize);
	void SetRotation(Quaternion newRotation);
	void SetOwner(Actor* pOwner);

	void RotateX(float pAngle);
	void RotateY(float pAngle);
	void RotateZ(float pAngle);

	Vector3D Right() const { return Vector3D(-mRotation.AsMatrixRow().mat[0][0], -mRotation.AsMatrixRow().mat[1][0], -mRotation.AsMatrixRow().mat[2][0]); }
	Vector3D Forward() const { return Vector3D(mRotation.AsMatrixRow().mat[0][1], mRotation.AsMatrixRow().mat[1][1], mRotation.AsMatrixRow().mat[2][1]); }
	Vector3D Up() const { return Vector3D(mRotation.AsMatrixRow().mat[0][2], mRotation.AsMatrixRow().mat[1][2], mRotation.AsMatrixRow().mat[2][2]); }

	float Pitch() const { return mPitch; }
	float Roll() const { return mRoll; }
	float Yaw() const { return mYaw; }
	void ComputeWorldTransform();

private:
	Vector3D mPosition;
	Vector3D mSize;
	Quaternion mRotation;
	Matrix4DRow mWorldTransform;
	Actor* mOwner;
	bool mNeedsToUpdate;
	float mRoll, mPitch, mYaw;
};

