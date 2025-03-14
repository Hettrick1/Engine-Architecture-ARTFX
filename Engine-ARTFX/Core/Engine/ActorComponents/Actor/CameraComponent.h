#pragma once

#include "Quaternion.h"
#include "Matrix4DRow.h"

class Actor;

class CameraComponent
{
public:
	CameraComponent(Actor* pOwner);
	~CameraComponent();

	void Update();

	void SetRelativeRotation(float pRelRoll, float pRelPitch, float pRelYaw);

	Quaternion GetRelativeRotation() const { return mRelRotation; }

	Vector3D Right() const { return Vector3D(-mRelRotation.AsMatrixRow().mat[0][0], -mRelRotation.AsMatrixRow().mat[1][0], -mRelRotation.AsMatrixRow().mat[2][0]); }
	Vector3D Forward() const { return Vector3D(mRelRotation.AsMatrixRow().mat[0][1], mRelRotation.AsMatrixRow().mat[1][1], mRelRotation.AsMatrixRow().mat[2][1]); } 
	Vector3D Up() const { return Vector3D(mRelRotation.AsMatrixRow().mat[0][2], mRelRotation.AsMatrixRow().mat[1][2], mRelRotation.AsMatrixRow().mat[2][2]); }

private :
	Actor* mOwner;
	float mRelPitch;
	float mRelYaw;
	float mRelRoll;
	Quaternion mRelRotation;
};

