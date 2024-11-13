#pragma once
#include "Window.h"
#include "../Graphics/Renderer.h"
#include "../../Scenes/Scene.h"
#include "../../Time.h"
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
	std::string mTitle;
	Window* mGameWindow;
	Renderer* mRenderer;
	bool mIsRunning;
	std::vector<Scene*> mAllScenes;
	int mLoadedScene;
};

