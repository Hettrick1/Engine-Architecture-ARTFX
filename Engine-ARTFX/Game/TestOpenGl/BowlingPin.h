#pragma once

#include "Actor.h"
#include "SpriteComponent.h"
#include "Physics/ICollisionListener.h"

class BowlingPin : public Actor, public ICollisionListener
{
public:
	BowlingPin(Vector3D pPos = 0, Vector3D pSize = 1, Quaternion pRotation = Quaternion(0, 0));
	~BowlingPin();
	void Start() override;
	void Update() override;
	void Destroy() override;
public:
	void OnTriggerEnter(ColliderComponent* collider) override;
	void OnCollision(ColliderComponent* collider) override;
	void OnTriggerStay(ColliderComponent* collider) override;
	void OnTriggerExit(ColliderComponent* collider) override;
};