#include "ColliderComponent.h"

ColliderComponent::ColliderComponent(Actor* owner, int updateOder) : Component(owner, updateOder)
{
	CollisionManager::GetInstance().RegisterCollider(this);
}

ColliderComponent::~ColliderComponent()
{
}

void ColliderComponent::OnStart()
{
}

void ColliderComponent::Update()
{
}

void ColliderComponent::OnEnd()
{
}

bool ColliderComponent::CheckCollisionWith(ColliderComponent* other)
{
	return true;
}

void ColliderComponent::OnCollision()
{
}

void ColliderComponent::OnTriggerEnter()
{
}

bool ColliderComponent::GetIsTriggerable()
{
	return mIsTriggerable;
}
