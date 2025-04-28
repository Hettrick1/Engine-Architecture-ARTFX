#pragma once

#include "Component.h"
#include "Physics/CollisionManager.h"
#include "Physics/HitResult.h"
#include <utility>
#include "Physics/AABB.h"
#include "Mesh.h"

struct HitResult;
class ICollisionListener;
class IRenderer;

enum class ColliderType
{
	Box,
	Sphere,
	Mesh,
	Box2D
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
	virtual bool CheckCollisionWith(ColliderComponent* other);
	virtual std::pair < Vector3D, Vector3D> GetCollisionPosition() const;
	virtual void DebugDraw(IRenderer& renderer);
	virtual AABB GetAABB() { return AABB(); }

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

	Mesh* GetMesh() const { return mMesh; }
	virtual ColliderType GetColliderType() = 0;
	std::vector<Vector3D> GetWorldVertices();

protected :
	bool mIsQuerry, mIsActive;;
	std::vector<ICollisionListener*> mListeners;
	Vector3D mSize;
	std::string mName;
	Mesh* mMesh;
};

