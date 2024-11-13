#pragma once
#include "Actor.h"
class Component
{
public:
	Component() = delete;
	Component(Actor* mOwner, int updateOder);
	virtual ~Component() {}
	virtual void OnStart();
	virtual void Update();
	virtual void OnEnd();

private:
	bool mIsActive;
	Actor* mOwner;
	int mUpdateOrder;
};

