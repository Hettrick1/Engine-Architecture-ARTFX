#include "LVLDoom.h"
#include "Doom/DoomPlayer.h"
#include "Doom/DoomPC.h"
#include "TestOpenGl/Cube.h"
#include "CameraActor.h"

LVLDoom::LVLDoom()
	: mPlayer(nullptr)
{
}

LVLDoom::~LVLDoom()
{
	if (mPlayer != nullptr)
	{
		delete mPlayer;
		mPlayer = nullptr;
	}
}

void LVLDoom::Start(IRenderer* renderer)
{
	Scene::Start(renderer);
	mPlayer = new DoomPlayer();
	AddActor(mPlayer);
	mPlayer->Start();
	Cube* cube = new Cube(3, 3);
	AddActor(cube);
	cube->Start();
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
