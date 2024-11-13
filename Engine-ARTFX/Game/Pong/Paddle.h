#pragma once

#include "../../Core/Maths/Vector2D.h"
#include "../../Core/Maths/Rectangle.h"
#include "../../Core/Engine/Debug Classes/Log.h"
#include <string>

class Paddle
{
private:
	Vector2D mPaddlePos;
	Vector2D mPaddleSpeed = { 0, 5 };
	Vector2D mPaddleSize = {40, 150};

public:
	Paddle(Vector2D paddlePos);
	~Paddle();
	void MovePlayer(float direction);
	void MoveIA(float speed);
	Rectangle& GetPaddleRect();
	Vector2D GetPaddlePos() { return mPaddlePos; }
	Vector2D GetPaddleSize() { return mPaddleSize; }
};

