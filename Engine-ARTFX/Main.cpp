#include "SDL.h"
#include "Game.h"
#include "SpaceInvader.h"
#include "BowlingOpenGl.h"
#include "LVLDoom.h"
#include "LVLAdvancedOpenGL.h"

int main(int argc, char** argv) {

	Game* pong = new Game("myGame", { new BowlingOpenGl()});

	return 0;
}