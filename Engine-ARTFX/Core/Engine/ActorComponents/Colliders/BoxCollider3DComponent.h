#pragma once
#include "ColliderComponent.h"
#include <utility>

class IRenderer;

class BoxCollider3DComponent : public ColliderComponent
{
public:
	BoxCollider3DComponent() = delete;
	BoxCollider3DComponent(Actor* pOwner, int pUpdateOder, Vector3D pSize = 1, Vector3D pRelativePosition = 0);
	~BoxCollider3DComponent();
	void OnStart() override;
	void Update() override;
	void OnEnd() override;

public:
	bool CheckCollisionWith(ColliderComponent* other) override;

public:
	bool CheckCollisionWithBox3D(BoxCollider3DComponent* other);

public:
	void SetShowInGame(bool pShowInGame);
	void SetSize(Vector3D pSize);

	void DebugDraw(IRenderer& renderer) override;

	Vector3D GetLastPosition();

	std::pair<Vector3D, Vector3D> GetCollisionPosition() const override { return mCollisionPosition; }

	AABB GetAABB() override;
private:
	Vector3D mPosition;
	Vector3D mLastPosition;
	std::pair<Vector3D, Vector3D> mCollisionPosition;
	bool mShowInGame;
};

