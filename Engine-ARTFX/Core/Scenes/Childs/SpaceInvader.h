#pragma once
#include "../Scene.h"

class SpaceInvader : public Scene
{
public:
	SpaceInvader();
	void Start(Renderer* renderer) override;
	void Update() override;
	void Render() override;
	void OnInput(SDL_Event event) override;
	void Close() override;
};

