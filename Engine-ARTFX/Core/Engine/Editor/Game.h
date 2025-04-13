#pragma once
#include "Window.h"
#include "IRenderer.h"
#include "Scene.h"
#include "Timer.h"
#include "InputManager.h"
#include "Physics/PhysicManager.h"
#include "CameraManager.h"
#include "SceneManager.h"
#include <iostream>
#include <vector>

class Game
{
public:
	Game(std::string title, Scene* pStartupScene);
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
	Scene* mStartUpScene;
	InputManager& mInputManager;
	PhysicManager& mPhysicManager;
	CameraManager& mCameraManager;
	bool mIsRunning;
};

