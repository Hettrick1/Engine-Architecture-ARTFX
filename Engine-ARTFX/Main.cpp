#include "SDL.h"
#include "Vector2D.h"
#include "Log.h"

int main(int argc, char** argv) {
	Vector2D myVector = Vector2D::One;
	myVector *= 2;

	Log::Info("" + static_cast<std::string>(myVector.Lenght()));

	return 0;
}