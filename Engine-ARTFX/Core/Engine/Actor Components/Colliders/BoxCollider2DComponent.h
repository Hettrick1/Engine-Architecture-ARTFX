#pragma once

#include "ColliderComponent.h"
#include "../../../Maths/Vector2D.h"

class BoxCollider2DComponent : public ColliderComponent
{
public:
	BoxCollider2DComponent() = delete;
	BoxCollider2DComponent(Actor* owner, int updateOder, Vector2D position, Vector2D size);
	~BoxCollider2DComponent();
	void OnStart() override;
	void Update() override;
	void OnEnd() override;

public:
	bool CheckCollisionWith(ColliderComponent* other) override;
	void OnCollision() override;

public:
	bool CheckCollisionWithBox(BoxCollider2DComponent* other);

	/*void OnCollisionEnter(); //Need to be implemented
	void OnCollisionQuit();
	void OnTriggerEnter();
	void OnTriggerStay();
	void OnTriggerQuit();*/
public:

private:
	Vector2D mPosition;
	Vector2D mSize;
};

