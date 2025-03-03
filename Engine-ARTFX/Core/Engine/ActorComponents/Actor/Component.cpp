#include "Component.h"
#include "Actor.h"

Component::Component(Actor* owner, int updateOder) : mIsActive(true), mOwner(owner), mUpdateOrder(updateOder)
{
	mOwner->AddComponent(this);
}

void Component::OnStart()
{
}

void Component::Update()
{
}

void Component::OnEnd()
{
}

Actor* Component::GetOwner()
{
	return mOwner;
}
