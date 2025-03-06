#pragma once
#include "ColliderComponent.h"
class BoxCollider3DComponent : public ColliderComponent
{
public:
	BoxCollider3DComponent() = delete;
	BoxCollider3DComponent(Actor* pOwner, int pUpdateOder, Vector3D pSize = 1);
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
private:
	Vector3D mPosition;
	Vector3D mSize;
	bool mShowInGame;
};

