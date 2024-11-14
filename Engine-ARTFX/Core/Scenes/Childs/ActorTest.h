#pragma once
#include "../Scene.h"

class ActorTest : public Scene
{
public:
	ActorTest();
	void Start(Renderer* renderer) override;
	void Update() override;
	void Render() override;
	void OnInput(SDL_Event event) override;
	void Close() override;
};

