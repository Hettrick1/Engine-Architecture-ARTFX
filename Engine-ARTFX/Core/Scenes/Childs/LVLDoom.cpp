#include "LVLDoom.h"
#include "Doom/DoomPlayer.h"

LVLDoom::LVLDoom()
	: mPlayer(nullptr)
{
}

LVLDoom::~LVLDoom()
{
}

void LVLDoom::Start(IRenderer* renderer)
{
	Scene::Start(renderer);
}

void LVLDoom::Update()
{
	Scene::Update();
}

void LVLDoom::Render()
{
	Scene::Render();
}

void LVLDoom::Close()
{
	Scene::Close();
}
