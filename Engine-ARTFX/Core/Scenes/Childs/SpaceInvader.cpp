#include "SpaceInvader.h"
#include "SpaceInvader/SpaceInvaderPlayer.h"

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
}

void SpaceInvader::Update()
{
	mPlayer->Update();
}

void SpaceInvader::Render()
{
	mRenderer->BeginDraw();
	mRenderer->Draw();
	mRenderer->EndDraw();
}

void SpaceInvader::OnInput(SDL_Event event)
{
}

void SpaceInvader::Close()
{
}
