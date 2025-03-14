#pragma once

#include "Actor.h"
#include "SpriteComponent.h"
#include "Physics/ICollisionListener.h"

class BowlingBall :public Actor, public ICollisionListener
{
public:
	BowlingBall(Vector3D pPos = 0, Vector3D pSize = 1, Quaternion pRotation = Quaternion(0, 0));
	~BowlingBall();
	void Start() override;
	void Update() override;
	void Destroy() override;
public:
	void OnTriggerEnter(ColliderComponent* collider) override;
	void OnCollision(ColliderComponent* collider) override;
	void OnTriggerStay(ColliderComponent* collider) override;
	void OnTriggerExit(ColliderComponent* collider) override;
};
