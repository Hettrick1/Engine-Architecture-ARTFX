#include "ActorMovementComponent.h"
#include "Actor.h"
#include "Timer.h"

ActorMovementComponent::ActorMovementComponent(Actor* pOwner, int pUpdateOrder)
	: Component(pOwner, pUpdateOrder), mSpeed(0.0f)
{
}

void ActorMovementComponent::SetSpeed(Vector2D pSpeed)
{
	mSpeed = pSpeed;
}

void ActorMovementComponent::SetSpeedX(float pSpeedX)
{
	mSpeed.x = pSpeedX;
}

void ActorMovementComponent::SetSpeedY(float pSpeedY)
{
	mSpeed.y = pSpeedY;
}

void ActorMovementComponent::Update()
{
	if(!Maths::NearZero(mSpeed.Length()))
	{
		Vector2D newPosition = mOwner->GetTransformComponent().GetPosition()
			+ (mOwner->GetTransformComponent().Right() * mSpeed.x
			+ mOwner->GetTransformComponent().Up() * mSpeed.y ) * Timer::deltaTime;
		mOwner->SetPosition(newPosition);
	}
}
