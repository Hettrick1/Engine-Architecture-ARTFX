#pragma once

#include "Component.h"
#include "CollisionManager.h"
#include "HitResult.h"

class ICollisionListener;

class ColliderComponent : public Component
{
public:
	ColliderComponent() = delete;
	ColliderComponent(Actor* owner, int updateOder);
	~ColliderComponent();

	bool GetIsTriggerable();
	virtual void Update();
	virtual bool CheckCollisionWith(ColliderComponent* other);

public:
	void AddListener(ICollisionListener* listener);
	void RemoveListener(ICollisionListener* listener);

public:
	void NotifyListenersStarted();
	void NotifyListenersStay();
	void NotifyListenersEnded();
	void SetHitResult(bool pHit, Actor* pHitActor, ColliderComponent* collision, Vector3D pNormal = 0, float pOverlap = 0);
	HitResult& GetHitResult();

	Vector3D GetSize() const { return mSize; }

protected :
	bool mIsTriggerable;
	std::vector<ICollisionListener*> mListeners;
	HitResult mHitResult;
	Vector3D mSize;
};

