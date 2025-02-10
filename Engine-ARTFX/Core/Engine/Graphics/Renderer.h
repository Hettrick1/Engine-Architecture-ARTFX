#pragma once
#include "../../Maths/Rectangle.h"
#include "../Editor/Window.h"
#include "SDL_image.h"

class Renderer
{
public:
	Renderer();
	Renderer(const Renderer&) = delete;
	Renderer& operator = (const Renderer&) = delete;

	bool Initialize(Window& rWindow);
	void BeginDraw();
	void EndDraw();
	void Close();

	void DrawRect(Rectangle& rRect);
	SDL_Renderer* ToSdlRenderer();
private:
	SDL_Renderer* mSdlRenderer;
};

