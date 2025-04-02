#pragma once

#include "Component.h"
#include "Physics/CollisionManager.h"
#include "Physics/HitResult.h"
#include <utility>
#include "Physics/AABB.h"

class ICollisionListener;
class IRenderer;

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
	virtual void DebugDraw(IRenderer& renderer);
	virtual AABB GetAABB() { return AABB(); }

public:
	void AddListener(ICollisionListener* listener);
	void RemoveListener(ICollisionListener* listener);

public:
	void NotifyListenersStarted();
	void NotifyListenersStay();
	void NotifyListenersEnded();

	void SetName(std::string pName) { mName = pName; }
	std::string GetName() const { return mName; }

	Vector3D GetSize() const { return mSize; }

protected :
	bool mIsTriggerable;
	std::vector<ICollisionListener*> mListeners;
	Vector3D mSize;
	std::string mName;
};

