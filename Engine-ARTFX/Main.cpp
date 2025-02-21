#include "SDL.h"
#include "Game.h"
#include "SpaceInvader.h"

int main(int argc, char** argv) {

	Game* pong = new Game("myGame", { new SpaceInvader()});

	return 0;
}