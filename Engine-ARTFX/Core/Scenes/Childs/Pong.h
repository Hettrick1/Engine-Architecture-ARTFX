#pragma once
#include "../Scene.h"
class Pong : public Scene
{
public:
	Pong();
	void Start(Renderer* renderer) override;
	void Update() override;
	void Render() override;
	void OnInput(SDL_Event event) override;
	void Close() override;
private:
	Vector2D mPlayerPos;
	Rectangle mPlayer;
};

