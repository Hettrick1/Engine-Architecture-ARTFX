#include "RigidbodyComponent.h"
#include "Physics/PhysicManager.h"
#include "ColliderComponent.h"
#include "Actor.h"
#include "Timer.h"
#include "Log.h"

RigidbodyComponent::RigidbodyComponent(Actor* pOwner, int pUpdateOrder)
	: Component(pOwner, pUpdateOrder), 
	mVelocity(0.0), mAcceleration(0.0), mMass(1.0), mFriction(0.1f), mUseGravity(false), mGravity(-9.81), 
	mBounciness(0.5), mIsGrounded(false), mIsStatic(false)
{
    PhysicManager::Instance().RegisterRigidBody(pOwner, this);
    pOwner->SetRigidBody(this);
}

void RigidbodyComponent::Update()
{
	if (mUseGravity && mGravity != 0 && !mIsGrounded)
	{
		mAcceleration.z += mMass * mGravity * 0.01;
	}

	mVelocity += mAcceleration;

	mVelocity *= (1.0f - mFriction * 0.1);

	mOwner->GetTransformComponent().Translate(mVelocity * Timer::deltaTime);

	mAcceleration = 0;
}

void RigidbodyComponent::ApplyForce(Vector3D pForce)
{
	if (mUseGravity)
	{
		mAcceleration += pForce / mMass;
	}
}

void RigidbodyComponent::AddImpulse(Vector3D pImpulse)
{
    if (mMass > 0.0f)
    {
        mVelocity += pImpulse / mMass;
    }
}

void RigidbodyComponent::ResolveCollision(Vector3D pResolveForce)
{
    if (mIsStatic || mMass > 10000)
    {
        return;
    }

	mAcceleration = pResolveForce;
}

void RigidbodyComponent::OnCollisionEnter(ColliderComponent* otherCollider)
{
    
}

void RigidbodyComponent::OnCollisionStay(ColliderComponent* otherCollider)
{

}

void RigidbodyComponent::OnCollisionExit(ColliderComponent* otherCollider)
{
   
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

void RigidbodyComponent::SetIsGrounded(bool pIsGrounded)
{
    mIsGrounded = pIsGrounded;
}

void RigidbodyComponent::SetGravity(float pGravity)
{
    mGravity = pGravity;
}

void RigidbodyComponent::SetIsStatic(bool isStatic)
{
    mIsStatic = isStatic;
}
