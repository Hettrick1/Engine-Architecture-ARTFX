#pragma once
#include "../Scene.h"

class SpaceInvaderPlayer;

class SpaceInvader : public Scene
{
public:
	SpaceInvader();
	~SpaceInvader();
	void Start(Renderer* renderer) override;
	void Update() override;
	void Render() override;
	void Close() override;
private:
	SpaceInvaderPlayer* mPlayer;
	SpaceInvaderPlayer* mPlayer2;
};

