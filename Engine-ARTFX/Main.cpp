#include "SDL.h"
#include "Core/Engine/Editor/Game.h"
#include "Core/Scenes/Childs/Pong.h"

int main(int argc, char** argv) {
	;
	Vector2D myVector = Vector2D::One;
	myVector *= 2;

	Game* pong = new Game("myGame", { new Pong()});

	Log::Info(std::to_string(myVector.Length()));

	return 0;
}