#pragma once

#include "../Component.h"
#include "../Managers/CollisionManager.h"

class Collider : public Component
{
public:
	Collider() = delete;
	Collider(Actor* owner, int updateOder);
	~Collider();
	virtual void OnStart();
	virtual void Update();
	virtual void OnEnd();

public:
	virtual bool CheckCollisionWith(Collider* other);
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

