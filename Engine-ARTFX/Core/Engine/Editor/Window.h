#pragma once
#include <SDL.h>
#include "../../Maths/Vector2D.h"
#include "../Debug Classes/Log.h"

class Window
{
public :
	Window(int width = 800, int height = 700);
	Window(const Window&) = delete;
	void operator = (const Window&) = delete;

	Vector2D GetDimensions() const;

	SDL_Window* GetSdlWindow() const;

	bool Open();
	void Close();

private:
	SDL_Window* mSdlWindow;
	Vector2D mDimensions;
};

