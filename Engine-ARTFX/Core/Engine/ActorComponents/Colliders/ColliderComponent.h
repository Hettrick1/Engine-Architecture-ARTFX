#pragma once

#include "Component.h"
#include "Physics/CollisionManager.h"
#include "Physics/HitResult.h"
#include <utility>
#include "Physics/AABB.h"

struct HitResult;
class ICollisionListener;
class IRenderer;
struct ContactManifold;

enum class ColliderType {
	BoxAABB,
	BoxSAT
};

class ColliderComponent : public Component
{
public:
	ColliderComponent() = delete;
	ColliderComponent(Actor* owner, int updateOder);
	~ColliderComponent();

	bool GetIsQuerry();
	void SetIsQuerry(bool isQuerry);
	virtual void Update();
	virtual bool CheckCollisionWith(ColliderComponent* other, ContactManifold& infosOut);
	virtual std::pair < Vector3D, Vector3D> GetCollisionPosition() const;
	virtual void DebugDraw(IRenderer& renderer);
	virtual AABB GetAABB() { return AABB(); }
	virtual ColliderType GetColliderType() const = 0;

public:
	void AddListener(ICollisionListener* listener);
	void RemoveListener(ICollisionListener* listener);

public:
	void NotifyListenersStarted(HitResult* infos);
	void NotifyListenersStay(HitResult* infos);
	void NotifyListenersEnded(HitResult* infos);

	void SetName(std::string pName) { mName = pName; }
	std::string GetName() const { return mName; }

	Vector3D GetSize() const { return mSize; }

	void SetActive(bool pActive);
	inline bool GetIsActive() const { return mIsActive; }

protected :
	bool mIsQuerry, mIsActive;;
	std::vector<ICollisionListener*> mListeners;
	Vector3D mSize;
	std::string mName;
};

