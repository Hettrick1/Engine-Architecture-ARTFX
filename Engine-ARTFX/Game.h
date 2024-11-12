#pragma once
#include "Window.h"
#include "Renderer.h"
#include <iostream>

class Game
{
public:
	Game(std::string title);
	~Game();
	void Initialize();
	void Loop();
	void Update();
	void Render();
	void Input();
	void Close();

private:
	std::string mTitle;
	Window* mGameWindow;
	Renderer* mRenderer;
	bool mIsRunning;
};

