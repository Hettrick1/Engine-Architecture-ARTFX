#pragma once
#include "../../Maths/Vector2D.h"
class Transform2D
{
public:

private:
	Vector2D mPosition = {0.0, 0.0};
	Vector2D mSize = {1.0, 1.0};
	float rotation = 0.0f;
};

