#include "SDL.h"
#include "Game.h"
#include "SpaceInvader.h"
#include "GlTestScene.h"

int main(int argc, char** argv) {

	Game* pong = new Game("myGame", { new GlTestScene()});

	return 0;
}