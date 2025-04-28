#pragma once

#include "ColliderComponent.h"
#include "Vector3D.h"

class BoxCollider2DComponent : public ColliderComponent
{
public:
	BoxCollider2DComponent() = delete;
	BoxCollider2DComponent(Actor* pOwner, int pUpdateOder, Vector3D pSize = 1);
	~BoxCollider2DComponent();
	void OnStart() override;
	void Update() override;
	void OnEnd() override;

public:
	bool CheckCollisionWith(ColliderComponent* other) override;

public:
	bool CheckCollisionWithBox(BoxCollider2DComponent* other);

public:
	void SetShowInGame(bool pShowInGame);
	void SetSize(Vector3D pSize);

	ColliderType GetColliderType() override { return ColliderType::Box2D; }

private:
	Vector3D mPosition;
	Vector3D mSize;
	bool mShowInGame;
};

