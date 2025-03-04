#pragma once

#include "Component.h"

class CameraComponent : public Component
{
public:
	CameraComponent(Actor* pOwner);
	~CameraComponent();

	void Update() override;
};

