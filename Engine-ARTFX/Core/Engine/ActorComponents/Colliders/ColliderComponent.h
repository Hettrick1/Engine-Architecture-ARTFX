#pragma once

#include "Component.h"
#include "Physics/CollisionManager.h"
#include "Physics/HitResult.h"
#include <utility>

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
	virtual std::pair < Vector3D, Vector3D> GetCollisionPosition() const;

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

