#pragma once
#include <vector>
#include "Scene.h"

class SceneManager
{
public:
	static Scene* ActiveScene;
	SceneManager() = default;
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;

	static void LoadScene(Scene* pScene);
	static void StartScene(IRenderer* pRenderer);
	static void Update();
	static void Render();
	static bool SceneLoaded();
	static void Unload();

private:
	static bool mIsSceneLoaded;
	
};