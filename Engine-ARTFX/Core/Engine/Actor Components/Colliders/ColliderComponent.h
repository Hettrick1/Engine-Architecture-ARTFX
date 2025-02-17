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

	virtual void Update();

public:
	virtual bool CheckCollisionWith(ColliderComponent* other);

public:
	bool GetIsTriggerable();
	void AddListener(ICollisionListener* listener);
	void RemoveListener(ICollisionListener* listener);

public:
	void NotifyListenersStarted();
	void NotifyListenersStay();
	void NotifyListenersEnded();
	void SetHitResult(bool pHit, Actor* pHitActor);
	HitResult& GetHitResult();

protected :
	bool mIsTriggerable;
	std::vector<ICollisionListener*> mListeners;
	HitResult mHitResult;
};

