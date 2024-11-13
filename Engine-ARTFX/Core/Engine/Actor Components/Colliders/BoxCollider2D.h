#pragma once

#include "Collider.h"
#include "../../../Maths/Vector2D.h"

class BoxCollider2D : public Collider
{
public:
	BoxCollider2D() = delete;
	BoxCollider2D(Actor* owner, int updateOder, Vector2D position, Vector2D size);
	~BoxCollider2D();
	void OnStart() override;
	void Update() override;
	void OnEnd() override;

public:
	void CheckCollisionWith(Collider* other) override;
	void OnCollision() override;

public:
	bool CheckCollisionWithBox(BoxCollider2D* other);

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

