#include "SDL.h"
#include "Game.h"
#include "SpaceInvader.h"

int main(int argc, char** argv) {
	;
	Vector2D myVector = Vector2D::One;
	myVector *= 2;

	Game* pong = new Game("myGame", { new SpaceInvader()});

	Log::Info(std::to_string(myVector.Length()));

	return 0;
}