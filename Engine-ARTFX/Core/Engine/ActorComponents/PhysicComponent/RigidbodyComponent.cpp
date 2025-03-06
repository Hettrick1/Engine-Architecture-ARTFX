#include "RigidbodyComponent.h"
#include "CollisionManager.h"
#include "ColliderComponent.h"
#include "Actor.h"
#include "Timer.h"
#include "Log.h"

RigidbodyComponent::RigidbodyComponent(Actor* pOwner, int pUpdateOrder)
	: Component(pOwner, pUpdateOrder), 
	mVelocity(0.0), mAcceleration(0.0), mMass(1.0), mFriction(0.1f), mUseGravity(true), mGravity(-9.81), 
	mBounciness(0.2)
{
	CollisionManager::Instance().RegisterRigidbody(pOwner, this); 
}

void RigidbodyComponent::Update()
{
	if (mUseGravity && mGravity < 0)
	{
		mAcceleration.z += mGravity;
	}

	mVelocity += mAcceleration * Timer::deltaTime;

	mVelocity *= (1.0f - mFriction * Timer::deltaTime);

	mOwner->GetTransformComponent().Translate(mVelocity * Timer::deltaTime);

	//Log::Info(std::to_string(mOwner->GetTransformComponent().GetPosition().z));

	mAcceleration = 0;
}

void RigidbodyComponent::ApplyForce(Vector3D pForce)
{
	if (mUseGravity)
	{
		mAcceleration += pForce / mMass;
	}
}

void RigidbodyComponent::OnCollisionEnter(ColliderComponent* otherCollider)
{
	if (!mUseGravity)
	{
		return;
	}
	if (mVelocity.Length() != 0)
	{
		mOwner->SetPosition(otherCollider->GetHitResult().hitLocation);
	}
	mVelocity = 0;
	mGravity = 0;
}

void RigidbodyComponent::OnCollisionExit(ColliderComponent* otherCollider)
{
	mGravity = -9.81;
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
