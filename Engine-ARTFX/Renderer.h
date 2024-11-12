#pragma once
#include "Rectangle.h"
#include "Window.h"

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

private:
	SDL_Renderer* mSdlRenderer;
};

