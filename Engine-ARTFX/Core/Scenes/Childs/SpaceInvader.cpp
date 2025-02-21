#include "SpaceInvader.h"
#include "SpaceInvader/SpaceInvaderPlayer.h"
#include "SpaceInvader/GroundActor.h"

SpaceInvader::SpaceInvader()
	: mPlayer(nullptr)
{
}

SpaceInvader::~SpaceInvader()
{
	delete mPlayer;

}

void SpaceInvader::Start(IRenderer* renderer)
{
	Scene::Start(renderer);
	mPlayer = new SpaceInvaderPlayer();
	mPlayer->Start();
	AddActor(mPlayer);
	GroundActor* ground = new GroundActor({ 0, 50 }, { 100, 1 }, 0);
	ground->Start();
	AddActor(ground);
	GroundActor* ground1 = new GroundActor({ 0, 750 }, { 100, 1 }, 0);
	ground1->Start();
	AddActor(ground1);
	GroundActor* ground2 = new GroundActor({ 50, 0 }, { 1, 100 }, 0);
	ground2->Start();
	AddActor(ground2);
	GroundActor* ground3 = new GroundActor({ 750, 0 }, { 1, 100 }, 0);
	ground3->Start();
	AddActor(ground3);
;
}

void SpaceInvader::Update()
{
	Scene::Update();
}

void SpaceInvader::Render()
{
	Scene::Render();
}

void SpaceInvader::Close()
{
}
