#include "Collider.h"

Collider::Collider(Actor* owner, int updateOder) : Component(owner, updateOder)
{
	CollisionManager::GetInstance().RegisterCollider(this);
}

Collider::~Collider()
{
}

void Collider::OnStart()
{
}

void Collider::Update()
{
}

void Collider::OnEnd()
{
}

bool Collider::CheckCollisionWith(Collider* other)
{
	return true;
}

void Collider::OnCollision()
{
}
