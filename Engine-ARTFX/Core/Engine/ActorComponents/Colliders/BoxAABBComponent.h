#pragma once
#include "ColliderComponent.h"
#include <utility>

class IRenderer;

class BoxAABBComponent : public ColliderComponent
{
public:
	BoxAABBComponent() = delete;
	BoxAABBComponent(Actor* pOwner, int pUpdateOder, Vector3D pSize = 1, Vector3D pRelativePosition = 0);
	~BoxAABBComponent();
	void OnStart() override;
	void Update() override;
	void OnEnd() override;

public:
	bool CheckCollisionWith(ColliderComponent* other) override;

public:
	void SetShowInGame(bool pShowInGame);
	void SetSize(Vector3D pSize);

	void DebugDraw(IRenderer& renderer) override;

	Vector3D GetLastPosition();

	std::pair<Vector3D, Vector3D> GetCollisionPosition() const override { return mCollisionPosition; }

	AABB GetAABB() override;
	ColliderType GetColliderType() const override { return ColliderType::BoxAABB; }

private:
	bool CheckCollisionWithBoxAABB(BoxAABBComponent* other);

private:
	Vector3D mPosition;
	Vector3D mLastPosition;
	std::pair<Vector3D, Vector3D> mCollisionPosition;
	bool mShowInGame;
};

