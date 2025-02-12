#pragma once
#include "../../Maths/Vector2D.h"
class Transform2D
{
public:
	Transform2D(Vector2D position, Vector2D size, float rotation);
	Transform2D();

	Vector2D GetPosition();
	Vector2D GetSize();
	float GetRotation();

	void SetPosition(Vector2D newPosition);
	void SetSize(Vector2D newSize);
	void SetRotation(float newRotation);

private:
	Vector2D mPosition;
	Vector2D mSize;
	float mRotation;
};

