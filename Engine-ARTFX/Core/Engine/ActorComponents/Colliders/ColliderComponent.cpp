#include "ColliderComponent.h"
#include "ICollisionListener.h"

ColliderComponent::ColliderComponent(Actor* owner, int updateOder)
	: Component(owner, updateOder), mIsTriggerable(true)
{

}

ColliderComponent::~ColliderComponent()
{
}

void ColliderComponent::Update()
{
}

bool ColliderComponent::CheckCollisionWith(ColliderComponent* other)
{
	return true;
}

bool ColliderComponent::GetIsTriggerable()
{
	return mIsTriggerable;
}

void ColliderComponent::AddListener(ICollisionListener* listener)
{
	mListeners.push_back(listener);
}

void ColliderComponent::RemoveListener(ICollisionListener* listenerToRemove)
{
	mListeners.erase(std::remove(mListeners.begin(), mListeners.end(), listenerToRemove), mListeners.end());
}

void ColliderComponent::NotifyListenersStarted()
{
	for (ICollisionListener* listener : mListeners) {
		listener->OnTriggerEnter(this);
	}
}

void ColliderComponent::NotifyListenersStay()
{
	for (ICollisionListener* listener : mListeners) {
		listener->OnTriggerStay(this);
	}
}

void ColliderComponent::NotifyListenersEnded()
{
	for (ICollisionListener* listener : mListeners) {
		listener->OnTriggerExit(this);
	}
}

void ColliderComponent::SetHitResult(bool pHit, Actor* pHitActor)
{
	mHitResult.bHit = pHit;
	mHitResult.hitActor = pHitActor;
	if (pHitActor != nullptr) {
		mHitResult.hitLocation = pHitActor->GetTransformComponent().GetPosition();
	}
}

HitResult& ColliderComponent::GetHitResult()
{
	return mHitResult;
}

