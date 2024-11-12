#pragma once
#include "../Scene.h"
class Pong : public Scene
{
public:
	Pong();
	void Start(Renderer* renderer) override;
	void Update() override;
	void Render() override;
	void OnInput(SDL_Event) override;
	void Close() override;
private:

};

