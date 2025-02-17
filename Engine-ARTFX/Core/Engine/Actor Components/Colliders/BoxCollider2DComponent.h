#pragma once

#include "ColliderComponent.h"
#include "Vector2D.h"

class BoxCollider2DComponent : public ColliderComponent
{
public:
	BoxCollider2DComponent() = delete;
	BoxCollider2DComponent(Actor* pOwner, int pUpdateOder, Vector2D pSize = 1);
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
	void SetSize(Vector2D pSize);
private:
	Vector2D mPosition;
	Vector2D mSize;
	bool mShowInGame;
};

