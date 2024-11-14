#pragma once
#include "../Engine/Graphics/Renderer.h"


class Scene
{
public:
	Scene(std::string title = "Scene");
	virtual void Start(Renderer* renderer);
	virtual void Update();
	virtual void Render();
	virtual void OnInput(SDL_Event);
	virtual void Close();


protected:
	std::string mTitle;
	Renderer* mRenderer;
};

