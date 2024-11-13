#pragma once

#include "../Component.h"

class Collider : public Component
{
public:
	Collider();
	~Collider();
	virtual void OnStart();
	virtual void Update();
	virtual void OnEnd();
public:
	virtual void CheckCollision();
	virtual void OnCollision();
	/*virtual void OnCollisionEnter(); //Need to be implemented
	virtual void OnCollisionQuit();
	virtual void OnTriggerEnter();
	virtual void OnTriggerStay();
	virtual void OnTriggerQuit();*/
};

