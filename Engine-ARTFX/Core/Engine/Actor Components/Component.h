#pragma once
#include "Actor.h"

class Actor;

class Component
{
public:
	Component() = delete;
	Component(Actor* owner, int updateOder);
	virtual ~Component() {}
	virtual void OnStart();
	virtual void Update();
	virtual void OnEnd();

private:
	bool mIsActive;
	Actor* mOwner;
	int mUpdateOrder;
};

