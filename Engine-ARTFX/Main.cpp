#include "SDL.h"
#include "Game.h"
#include "SpaceInvader.h"
#include "BowlingOpenGl.h"
#include "LVLDoom.h"

int main(int argc, char** argv) {

	Game* pong = new Game("myGame", { new LVLDoom()});

	return 0;
}