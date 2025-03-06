#include "RigidbodyComponent.h"
#include "Actor.h"
#include "Timer.h"
#include "Log.h"

float RigidbodyComponent::GRAVITY = -9.81;

RigidbodyComponent::RigidbodyComponent(Actor* pOwner, int pUpdateOrder)
	: Component(pOwner, pUpdateOrder), 
	mVelocity(0.0), mAcceleration(0.0), mMass(1.0), mFriction(0.1f), mUseGravity(true)
{
}

void RigidbodyComponent::Update()
{
	if (mUseGravity)
	{
		mAcceleration.z += GRAVITY;
	}

	mVelocity += mAcceleration * Timer::deltaTime;

	mVelocity *= (1.0f - mFriction * Timer::deltaTime);

	mOwner->GetTransformComponent().Translate(mVelocity * Timer::deltaTime);

	Log::Info(std::to_string(mOwner->GetTransformComponent().GetPosition().z));

	mAcceleration = 0;
}

void RigidbodyComponent::ApplyForce(Vector3D pForce)
{
	mAcceleration += pForce / mMass;
}

void RigidbodyComponent::SetVelocity(Vector3D pVelocity)
{
	mVelocity = pVelocity;
}

void RigidbodyComponent::SetMass(float pMass)
{
	mMass = (pMass > 0.0) ? pMass : 1.0f;
}

void RigidbodyComponent::SetUseGravity(bool pUseGravity)
{
	mUseGravity = pUseGravity;
}
