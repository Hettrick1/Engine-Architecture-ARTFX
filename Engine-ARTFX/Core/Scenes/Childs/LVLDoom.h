#pragma once
#include "Scene.h"
#include "Doom/DoomPlayer.h"

class DoomPlayer;

class LVLDoom : public Scene
{
public:
	LVLDoom();
	~LVLDoom();
	void Start(IRenderer* renderer) override;
	void Update() override;
	void Render() override;
	void Close() override;
private:
	DoomPlayer* mPlayer;
};


