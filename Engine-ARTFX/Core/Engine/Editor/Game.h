#pragma once
#include "Window.h"
#include "IRenderer.h"
#include "Scene.h"
#include "Timer.h"
#include "InputManager.h"
#include "CollisionManager.h"
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
	IRenderer* mRenderer;
	InputManager& mInputManager;
	CollisionManager& mCollisionManager;
	bool mIsRunning;
	std::vector<Scene*> mAllScenes;
	int mLoadedScene;
};

