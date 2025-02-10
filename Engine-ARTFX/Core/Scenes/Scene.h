#pragma once
#include "../Engine/Graphics/Renderer.h"
#include <vector>

class Actor;

class Scene
{
public:
	static Scene* ActiveScene;
	Scene(std::string title = "Scene");
	virtual void Start(Renderer* renderer);
	virtual void Update();
	virtual void Render();
	virtual void OnInput(SDL_Event);
	virtual void Close();

public:
	virtual void AddActor(Actor* actor);
	virtual void UpdateAllActors();
	virtual void RemoveActor(Actor* actor);

protected:
	std::string mTitle;
	Renderer* mRenderer;
	std::vector<Actor*> mAllActors;
	std::vector<Actor*> mPendingActors;
	bool mIsUpdatingActor;
};

