#pragma once
#include "IRenderer.h"
#include <vector>
#include "Assets.h"

class Actor;

class Scene
{
public:
	Scene(std::string title = "Scene");
	virtual void Start(IRenderer* renderer);
	virtual void Load();
	virtual void Update();
	virtual void Render();
	virtual void Unload();
	virtual void Close();

public:
	virtual void AddActor(Actor* actor);
	virtual void UpdateAllActors();
	virtual void RemoveActor(Actor* actor);

public : 
	IRenderer* GetRenderer() const { return mRenderer; }

protected:
	std::string mTitle;
	IRenderer* mRenderer;
	std::vector<Actor*> mAllActors;
	std::vector<Actor*> mPendingActors;
	bool mIsUpdatingActor;
};

