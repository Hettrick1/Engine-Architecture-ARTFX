#include "Scene.h"

Scene::Scene(std::string title) : mTitle(title)
{
}

void Scene::Start(Renderer* renderer)
{
	mRenderer = renderer;
}

void Scene::Update()
{
}

void Scene::Render()
{
}

void Scene::OnInput(SDL_Event)
{
}

void Scene::Close()
{
}
