#pragma once

#include "../Component.h"
#include "../Managers/CollisionManager.h"

class ColliderComponent : public Component
{
public:
	ColliderComponent() = delete;
	ColliderComponent(Actor* owner, int updateOder);
	~ColliderComponent();
	virtual void OnStart();
	virtual void Update();
	virtual void OnEnd();

public:
	virtual bool CheckCollisionWith(ColliderComponent* other);
	virtual void OnCollision();
	virtual void OnTriggerEnter();
	/*
	virtual void OnTriggerStay();
	virtual void OnTriggerQuit();*/

public:
	bool GetIsTriggerable();

protected :
	bool mIsTriggerable;
};

