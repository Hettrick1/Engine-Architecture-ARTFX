#pragma once
#include "Actor.h"
#include "IActionListener.h"
#include "SpriteComponent.h"
#include "ICollisionListener.h"

class GroundActor : public Actor, public ICollisionListener
{
public:
	GroundActor(Vector2D pPos = 0, Vector2D pSize = 1, float pRotation = 0);
	~GroundActor();
	void Start() override;
	void Update() override;
	void Destroy() override;
public:
	void OnTriggerEnter(ColliderComponent* collider) override;
	void OnCollision(ColliderComponent* collider) override;
	void OnTriggerStay(ColliderComponent* collider) override;
	void OnTriggerExit(ColliderComponent* collider) override;
};

