#pragma once
#include "Actor.h"
#include "IActionListener.h"
#include "FlipbookComponent.h"
#include "ICollisionListener.h"

class SpaceInvaderPlayer : public Actor, ICollisionListener
{
public:
	SpaceInvaderPlayer();
	~SpaceInvaderPlayer();
	void Start() override;
	void Update() override;
	void Destroy() override;
public :
	void OnTriggerEnter(ColliderComponent* collider) override;
	void OnCollision(ColliderComponent* collider) override;
	void OnTriggerStay(ColliderComponent* collider) override;
	void OnTriggerExit(ColliderComponent* collider) override;
private:
};

