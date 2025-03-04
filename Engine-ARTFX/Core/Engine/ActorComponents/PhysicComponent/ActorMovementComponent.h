#pragma once

#include "Component.h"
#include "Vector3D.h"
#include "Maths.h"

class Actor;

class ActorMovementComponent : public Component
{
public:
	ActorMovementComponent(Actor* pOwner, int pUpdateOrder = 100);
	ActorMovementComponent() = delete;
	ActorMovementComponent(const ActorMovementComponent&) = delete;
	ActorMovementComponent& operator=(const ActorMovementComponent&) = delete;

	Vector3D GetSpeed() const { return mSpeed; }

	void SetSpeed(Vector3D pSpeed);
	void SetSpeedX(float pSpeedX);
	void SetSpeedY(float pSpeedY);
	void SetSpeedZ(float pSpeedZ);

	void Update() override;
protected:
	Vector3D mSpeed;
};

