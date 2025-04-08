#pragma once

#include "Quaternion.h"
#include "Matrix4DRow.h"
#include "Component.h"

class Actor;

class CameraComponent : public Component
{
public:
	CameraComponent(Actor* pOwner, int updateOder = 0);
	~CameraComponent();

	Matrix4DRow GetWorldTransform();
	void ComputeRelativeTransform();

	void UpdateCam();
};

