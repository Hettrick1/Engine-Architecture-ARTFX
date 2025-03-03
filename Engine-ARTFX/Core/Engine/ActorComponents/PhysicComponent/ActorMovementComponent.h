#pragma once

#include "Component.h"
#include "Vector2D.h"
#include "Maths.h"

class Actor;

class ActorMovementComponent : public Component
{
public:
	ActorMovementComponent(Actor* pOwner, int pUpdateOrder = 100);
	ActorMovementComponent() = delete;
	ActorMovementComponent(const ActorMovementComponent&) = delete;
	ActorMovementComponent& operator=(const ActorMovementComponent&) = delete;

	Vector2D GetSpeed() const { return mSpeed; }

	void SetSpeed(Vector2D pSpeed);
	void SetSpeedX(float pSpeedX);
	void SetSpeedY(float pSpeedY);

	void Update() override;
protected:
	Vector2D mSpeed;
};

