#pragma once

#include "Collider.h"
#include "../../../Maths/Vector2D.h"

class BoxCollider2D : public Collider
{
public:
	BoxCollider2D() = delete;
	BoxCollider2D(Vector2D position, Vector2D size);
	~BoxCollider2D();
	void OnStart() override;
	void Update() override;
	void OnEnd() override;

public:
	void CheckCollision() override;
	void OnCollision() override;

	/*void OnCollisionEnter(); //Need to be implemented
	void OnCollisionQuit();
	void OnTriggerEnter();
	void OnTriggerStay();
	void OnTriggerQuit();*/

private:
	Vector2D mPosition;
	Vector2D mSize;
};

