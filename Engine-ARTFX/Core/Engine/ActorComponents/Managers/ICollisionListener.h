#pragma once
#include "ColliderComponent.h"

class ICollisionListener {
public:
	virtual ~ICollisionListener() = default;
	virtual void OnCollision(ColliderComponent* collider) = 0;
	virtual void OnTriggerEnter(ColliderComponent* collider) = 0;
	virtual void OnTriggerStay(ColliderComponent* collider) = 0;
	virtual void OnTriggerExit(ColliderComponent* collider) = 0;
};
