#include "SDL.h"
#include "Game.h"
#include "SpaceInvader.h"
#include "BowlingOpenGl.h"
#include "LVLDoom.h"
#include "LVLAdvancedOpenGL.h"
#include "LVLDoomMainMenu.h"
#include "SplashScreen.h"

int main(int argc, char** argv) {

	Game* pong = new Game("myGame", new SplashScreen(new LVLDoomMainMenu()));

	return 0;
}