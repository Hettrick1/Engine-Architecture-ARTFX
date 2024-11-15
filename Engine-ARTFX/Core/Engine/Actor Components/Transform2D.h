#pragma once
#include "../../Maths/Vector2D.h"
class Transform2D
{
public:
	Transform2D(Vector2D position, Vector2D size, float rotation);
	Transform2D() = delete;

	Vector2D GetPosition();
	Vector2D GetSize();
	float GetRotation();

	void SetPosition(Vector2D newPosition);
	void SetSize(Vector2D newSize);
	void SetRotation(float newRotation);

private:
	Vector2D mPosition = {0.0, 0.0};
	Vector2D mSize = {1.0, 1.0};
	float mRotation = 0.0f;
};

