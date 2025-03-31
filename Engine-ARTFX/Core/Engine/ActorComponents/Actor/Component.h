#pragma once
#include "Matrix4DRow.h"
#include "Vector3D.h"

class Actor;

class Component
{
public:
	Component() = delete;
	Component(Actor* owner, int updateOder = 0);
	virtual ~Component();
	virtual void OnStart();
	virtual void Update();
	virtual void OnEnd();

	void SetRelativePosition(Vector3D pPosition);
	void SetRelativeSize(Vector3D pSize);
	void SetRelativeRotation(Quaternion pRotation);
	void RelativeRotateX(float pAngle);
	void RelativeRotateY(float pAngle);
	void RelativeRotateZ(float pAngle);

	Matrix4DRow GetWorldTransform();
	void ComputeRelativeTransform();
	Matrix4DRow GetRelativeTransform() const { return mRelativeTransform; }
	Vector3D RelativeRight() const
	{
		return Vector3D(-mRelativeTransform.mat[0][0], -mRelativeTransform.mat[1][0], -mRelativeTransform.mat[2][0]);
	}

	Vector3D RelativeForward() const
	{
		return Vector3D(mRelativeTransform.mat[0][1], mRelativeTransform.mat[1][1], mRelativeTransform.mat[2][1]);
	}

	Vector3D RelativeUp() const
	{
		return Vector3D(mRelativeTransform.mat[0][2], mRelativeTransform.mat[1][2], mRelativeTransform.mat[2][2]);
	}
	Actor* GetOwner();

protected:
	bool mIsActive;
	Actor* mOwner;
	int mUpdateOrder;
	Matrix4DRow mRelativeTransform;
	Vector3D mRelativePosition;
	Vector3D mRelativeSize;
	Quaternion mRelativeRotation;
};

