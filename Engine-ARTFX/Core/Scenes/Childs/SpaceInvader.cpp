#include "SpaceInvader.h"
#include "SpaceInvader/SpaceInvaderPlayer.h"

SpaceInvader::SpaceInvader()
	: mPlayer(nullptr), mPlayer2(nullptr)
{
}

SpaceInvader::~SpaceInvader()
{
	delete mPlayer;
	delete mPlayer2;
}

void SpaceInvader::Start(Renderer* renderer)
{
	Scene::Start(renderer);
	mPlayer = new SpaceInvaderPlayer();
	mPlayer->Start();
	mPlayer2 = new SpaceInvaderPlayer();
	mPlayer2->Start();
	mPlayer2->SetPosition(Vector2D(490, 500));
}

void SpaceInvader::Update()
{
	mPlayer->Update();
	mPlayer2->Update();
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
