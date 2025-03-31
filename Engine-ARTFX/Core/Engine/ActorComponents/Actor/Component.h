#pragma once

class Actor;

class Component
{
public:
	Component() = delete;
	Component(Actor* owner, int updateOder = 0);
	virtual ~Component();
	virtual void OnStart();
	virtual void Update();
	virtual void OnEnd();
	Actor* GetOwner();

protected:
	bool mIsActive;
	Actor* mOwner;
	int mUpdateOrder;
};

