#include "Scene.h"

#include "Actor.h"
#include "Physics/PhysicManager.h"
#include "CameraManager.h"
#include <algorithm>


Scene::Scene(std::string title) 
	: mTitle(title), mIsUpdatingActor(false), mRenderer(nullptr)
{
}

void Scene::Start(IRenderer* renderer)
{
	mRenderer = renderer;
}

void Scene::Load()
{
}

void Scene::Update()
{
	UpdateAllActors();
}

void Scene::Render()
{
	mRenderer->BeginDraw();
	mRenderer->Draw();
	mRenderer->EndDraw();
}

void Scene::Unload()
{
	mRenderer->Unload();
	PhysicManager::Instance().Unload();
	CameraManager::Instance().Unload();
	while (!mAllActors.empty()) {
		mAllActors.back()->Destroy();
		delete mAllActors.back();
		mAllActors.pop_back();
	}
	while (!mPendingActors.empty()) {
		mPendingActors.back()->Destroy();
		delete mPendingActors.back();
		mAllActors.pop_back();
	}
	Assets::Clear();
}

void Scene::Close()
{
	mRenderer->Unload();
	PhysicManager::Instance().Unload();
	CameraManager::Instance().Unload();
	while (!mAllActors.empty()) {
		mAllActors.back()->Destroy();
		delete mAllActors.back();
		mAllActors.pop_back();
	}
	while (!mPendingActors.empty()) {
		mPendingActors.back()->Destroy();
		delete mPendingActors.back();
		mAllActors.pop_back();
	}
}

void Scene::AddActor(Actor* actor)
{
	actor->AttachScene(*this);
	if (mIsUpdatingActor) 
	{ 
		mPendingActors.emplace_back(actor); 
	}
	else
	{
		mAllActors.emplace_back(actor);
	}
}

void Scene::UpdateAllActors()
{
	mIsUpdatingActor = true;
	for (Actor* actor : mAllActors) 
	{
		actor->Update();
	}
	mIsUpdatingActor = false;
	for (Actor* actor : mPendingActors) 
	{
		mAllActors.emplace_back(actor);
	}
	mPendingActors.clear();
	for (Actor* actor : mAllActors) 
	{
		if (actor->GetState() == ActorState::Dead)
		{
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
