#pragma once

#include "Vector2D.h"
#include "Maths.h"

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
	Vector2D Right() const { return Vector2D(Maths::Cos(mRotation), -Maths::Sin(mRotation)); }
	Vector2D Up() const { return Vector2D(Maths::Sin(mRotation), -Maths::Cos(mRotation)); }

private:
	Vector2D mPosition;
	Vector2D mSize;
	float mRotation;
};

