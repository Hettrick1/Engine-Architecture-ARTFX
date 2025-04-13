#include "SceneManager.h"

bool SceneManager::mIsSceneLoaded = false;
Scene* SceneManager::ActiveScene = nullptr;

void SceneManager::LoadScene(Scene* pScene)
{
	IRenderer* renderer = nullptr;
	if (ActiveScene != nullptr)
	{
		ActiveScene->Close();
		renderer = ActiveScene->GetRenderer();
		delete ActiveScene;
		ActiveScene = nullptr;
	}
	ActiveScene = pScene;
	ActiveScene->Load();
	if (renderer != nullptr)
	{
		ActiveScene->Start(renderer);
	}
	mIsSceneLoaded = true;
}

void SceneManager::StartScene(IRenderer* pRenderer)
{
	ActiveScene->Start(pRenderer);
}

void SceneManager::Update()
{
	ActiveScene->Update();
}

void SceneManager::Render()
{
	ActiveScene->Render();
}

bool SceneManager::SceneLoaded()
{
	return mIsSceneLoaded;
}

void SceneManager::Unload()
{
	ActiveScene->Unload();
}
