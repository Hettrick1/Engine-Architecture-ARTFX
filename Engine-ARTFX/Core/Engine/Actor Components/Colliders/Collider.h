#pragma once

#include "../Component.h"

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
	virtual void CheckCollisionWith(Collider* other);
	virtual void OnCollision();
	/*virtual void OnCollisionEnter(); //Need to be implemented
	virtual void OnCollisionQuit();
	virtual void OnTriggerEnter();
	virtual void OnTriggerStay();
	virtual void OnTriggerQuit();*/
};

