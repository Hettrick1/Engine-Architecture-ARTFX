#include "Scene.h"

#include "../Engine/Actor Components/Actor.h"
#include <algorithm>

Scene* Scene::ActiveScene = nullptr;

Scene::Scene(std::string title) : mTitle(title)
{
}

void Scene::Start(Renderer* renderer)
{
	mRenderer = renderer;
}

void Scene::Load()
{
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

void Scene::Unload()
{
	while (!mAllActors.empty()) {
		delete mAllActors.back();
	}
	Assets::Clear();
}

void Scene::Close()
{
}

void Scene::AddActor(Actor* actor)
{
	actor->AttachScene(*this);
	if (mIsUpdatingActor) { mPendingActors.emplace_back(actor); }
	else mAllActors.emplace_back(actor);
}

void Scene::UpdateAllActors()
{
	mIsUpdatingActor = true;
	for (Actor* actor : mAllActors) {
		actor->Update();
	}
	mIsUpdatingActor = false;
	for (Actor* actor : mPendingActors) {
		mAllActors.emplace_back(actor);
	}
	mPendingActors.clear();
	for (Actor* actor : mAllActors) {
		if (actor->GetState() == ActorState::Dead) {
			delete actor;
		}
	}
}

void Scene::RemoveActor(Actor* actor)
{
	std::vector<Actor*>::iterator it = find(mPendingActors.begin(), mPendingActors.end(), actor); 
	if (it != mPendingActors.end())
	{
		iter_swap(it, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}
	it = find(mAllActors.begin(), mAllActors.end(), actor);
	if (it != mAllActors.end())
	{
		iter_swap(it, mAllActors.end() - 1);
		mAllActors.pop_back(); 
	}

}
