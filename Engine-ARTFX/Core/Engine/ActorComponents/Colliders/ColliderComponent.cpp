#include "ColliderComponent.h"
#include "Physics/ICollisionListener.h"
#include "Physics/PhysicManager.h"
#include "Scene.h"
#include "IRenderer.h"

ColliderComponent::ColliderComponent(Actor* pOwner, int pUpdateOder)
	: Component(pOwner, pUpdateOder), mIsTriggerable(false)
{
	PhysicManager::Instance().RegisterCollider(pOwner, this);
	mOwner->GetScene().GetRenderer()->AddDebugCollider(this);
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

std::pair<Vector3D, Vector3D> ColliderComponent::GetCollisionPosition() const
{
	return std::pair<Vector3D, Vector3D>();
}

void ColliderComponent::DebugDraw(IRenderer& renderer)
{
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


