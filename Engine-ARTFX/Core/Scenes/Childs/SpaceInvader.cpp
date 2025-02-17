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

void SpaceInvader::Start(Renderer* renderer)
{
	Scene::Start(renderer);
	mPlayer = new SpaceInvaderPlayer();
	mPlayer->Start();
	AddActor(mPlayer);
	GroundActor* ground = new GroundActor({ 0, 100 }, { 100, 1 }, 0);
	ground->Start();
	AddActor(ground);
;
}

void SpaceInvader::Update()
{
	Scene::Update();
}

void SpaceInvader::Render()
{
	mRenderer->BeginDraw();
	mRenderer->Draw();
	mRenderer->EndDraw();
}

void SpaceInvader::Close()
{
}
