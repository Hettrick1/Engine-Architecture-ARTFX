#include "SDL.h"
#include "Game.h"

int main(int argc, char** argv) {
	Vector2D myVector = Vector2D::One;
	myVector *= 2;

	Game* game = new Game("myGame");

	Log::Info(std::to_string(myVector.Length()));

	return 0;
}