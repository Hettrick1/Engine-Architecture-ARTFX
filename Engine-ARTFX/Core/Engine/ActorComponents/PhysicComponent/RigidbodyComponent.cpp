#include "RigidbodyComponent.h"
#include "CollisionManager.h"
#include "ColliderComponent.h"
#include "Actor.h"
#include "Timer.h"
#include "Log.h"

RigidbodyComponent::RigidbodyComponent(Actor* pOwner, int pUpdateOrder)
	: Component(pOwner, pUpdateOrder), 
	mVelocity(0.0), mAcceleration(0.0), mMass(1.0), mFriction(0.1f), mUseGravity(true), mGravity(-9.81), 
	mBounciness(0.5), mIsGrounded(false), mIsStatic(false)
{
	CollisionManager::Instance().RegisterRigidbody(pOwner, this); 
}

void RigidbodyComponent::Update()
{
	if (mUseGravity && mGravity != 0 && !mIsGrounded)
	{
		mAcceleration.z += mMass * mGravity;
	}

	mVelocity += mAcceleration * Timer::deltaTime;

	mVelocity *= (1.0f - mFriction * Timer::deltaTime);

	mOwner->GetTransformComponent().Translate(mVelocity * 0.5 * Timer::deltaTime);

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

void RigidbodyComponent::AddImpulse(Vector3D pImpulse)
{
    if (mMass > 0.0f)
    {
        mVelocity += pImpulse / mMass;
    }
}

void RigidbodyComponent::OnCollisionEnter(ColliderComponent* otherCollider)
{
    Log::Info("aaaaaaaaaaa");
    if (mIsStatic || !mUseGravity || mMass > 1000000)
    {
        return;
    }
    HitResult hit = otherCollider->GetHitResult();
    Vector3D n = hit.Normal;

    if (mIsGrounded && hit.Normal.z > 0.01f)
    {
        return;
    }
    mOwner->GetTransformComponent().Translate(n * (hit.Depth + 0.001f));

    // Get if existing the other rigidbody
    RigidbodyComponent* otherRb = CollisionManager::Instance().GetRigidbody(otherCollider->GetOwner());

    bool isGround = false;

    if (otherRb) {
        isGround = otherRb->IsStatic() || (otherRb->GetMass() > mMass * 10.0f) || otherRb->GetIsGrounded();
    }
    else {
        isGround = true;
    }

    if (isGround && hit.Normal.z > 0.01f) {
        mIsGrounded = true;
        mVelocity.z = 0.0f; 
    }

    if (mIsGrounded && mUseGravity) {
        mAcceleration.z = 0.0f;
    }

    Vector3D otherVelocity = (otherRb && !isGround) ? otherRb->GetVelocity() : Vector3D(0);

    // Calculate Velocity relative to the normal
    Vector3D relativeVelocity = mVelocity - otherVelocity;
    float vRel = Vector3D::Dot(relativeVelocity, n);

    if (vRel >= 0)
        return;

    // bounciness
    float e = mBounciness;

    // calculate invert mass
    float invMass1 = (mMass > 0.0f) ? 1.0f / mMass : 0.0f;
    float invMass2 = (otherRb && otherRb->GetMass() > 0.0f) ? 1.0f / otherRb->GetMass() : 0.0f;

    // calculate impulse
    float j = -(1 + e) * vRel / (invMass1 + invMass2);

    const float impulseThreshold = 0.8f;
    if (fabs(j) < impulseThreshold * mMass)
    {
        SetVelocity(0);
        j = 0;
        return;
    }

    Vector3D impulse = j * n;

    // apply impulse
    mVelocity += impulse * invMass1;

    if (otherRb)
    {
        otherRb->SetVelocity(otherRb->GetVelocity() - impulse * invMass2);
    }
}

void RigidbodyComponent::OnCollisionStay(ColliderComponent* otherCollider)
{

}

void RigidbodyComponent::OnCollisionExit(ColliderComponent* otherCollider)
{
    RigidbodyComponent* otherRb = CollisionManager::Instance().GetRigidbody(otherCollider->GetOwner()); 

    bool isGround = false;

    if (otherRb) {
        isGround = otherRb->IsStatic() || (otherRb->GetMass() > mMass * 10.0f);
    }
    else {
        isGround = true;
    }

    if (isGround)
    {
        mIsGrounded = false;
        otherRb->SetIsGrounded(false);
        mGravity = -9.81;
    }
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
