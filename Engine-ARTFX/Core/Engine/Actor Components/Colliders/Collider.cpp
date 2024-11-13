#include "Collider.h"

Collider::Collider(Actor* owner, int updateOder) : Component(owner, updateOder)
{
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

void Collider::CheckCollisionWith(Collider* other)
{
}

void Collider::OnCollision()
{
}
