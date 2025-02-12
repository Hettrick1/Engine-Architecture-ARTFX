#pragma once
#include "Window.h"
#include "Renderer.h"
#include "Scene.h"
#include "Timer.h"
#include <iostream>
#include <vector>

class Game
{
public:
	Game(std::string title, std::vector<Scene*> scenes);
	~Game();
	void Initialize();
	void Loop();
	void Update();
	void Render();
	void Input();
	void Close();

private:
	SDL_Event mSdlEvent;
	std::string mTitle;
	Window* mGameWindow;
	Renderer* mRenderer;
	bool mIsRunning;
	std::vector<Scene*> mAllScenes;
	int mLoadedScene;
};

