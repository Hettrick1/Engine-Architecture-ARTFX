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
	void Update() override;
	void ApplyForce(Vector3D pForce);
	void OnCollisionEnter(ColliderComponent* otherCollider);
	void OnCollisionExit(ColliderComponent* otherCollider);
public:
	void SetVelocity(Vector3D pVelocity);
	void SetMass(float pMass);
	void SetUseGravity(bool pUseGravity);
	Vector3D Getvelocity() const { return mVelocity; }
	float GetMass() const { return mMass; }

private:
	Vector3D mVelocity;
	Vector3D mAcceleration;
	float mMass;
	float mFriction;
	bool mUseGravity;
	float mGravity;
	float mBounciness;
};

