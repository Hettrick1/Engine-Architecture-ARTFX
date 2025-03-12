#pragma once

#include "Component.h"
#include "Vector3D.h"
#include "Maths.h"

class Actor;
class ColliderComponent;

class RigidbodyComponent : public Component
{
public:
	RigidbodyComponent(Actor* pOwner, int pUpdateOrder = 100);
	RigidbodyComponent() = delete;
	RigidbodyComponent(const RigidbodyComponent&) = delete;
	RigidbodyComponent& operator=(const RigidbodyComponent&) = delete;
public :
	void Update();
	void ApplyForce(Vector3D pForce);
	void AddImpulse(Vector3D pImpulse);
	void ResolveCollision(Vector3D pResolveForce);
	void OnCollisionEnter(ColliderComponent* otherCollider);
	void OnCollisionStay(ColliderComponent* otherCollider);
	void OnCollisionExit(ColliderComponent* otherCollider);
public:
	void SetVelocity(Vector3D pVelocity);
	void SetMass(float pMass);
	void SetUseGravity(bool pUseGravity);
	void SetIsGrounded(bool pIsGrounded);
	void SetGravity(float pGravity);
	Vector3D GetVelocity() const { return mVelocity; }
	float GetMass() const { return mMass; }
	bool GetIsGrounded() const { return mIsGrounded; }
	void SetBounciness(float bounce) { bounce <= 1 ? mBounciness = bounce : mBounciness = 1.0f; }
	float GetBounciness() const { return mBounciness; }

	void SetIsStatic(bool isStatic);
	bool IsStatic() const { return mIsStatic; }

private:
	Vector3D mVelocity;
	Vector3D mAcceleration;
	float mMass;
	float mFriction;
	bool mUseGravity;
	float mGravity;
	float mBounciness;
	bool mIsGrounded, mIsStatic;
};

