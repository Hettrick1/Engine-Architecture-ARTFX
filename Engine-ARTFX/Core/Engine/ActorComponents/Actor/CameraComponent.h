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

	void Update();

	inline Matrix4DRow GetViewMatrix() const { return mViewMatrix; }
private :
	Matrix4DRow mViewMatrix;
};

