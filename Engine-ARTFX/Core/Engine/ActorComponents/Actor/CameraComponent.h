#pragma once

#include "Component.h"

class CameraComponent : public Component
{
	CameraComponent(Actor* pOwner);
	~CameraComponent();

	void Update() override;
};

