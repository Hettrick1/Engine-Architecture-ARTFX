#include "SpaceInvader.h"
#include "SpaceInvader/SpaceInvaderPlayer.h"

SpaceInvader::SpaceInvader()
{
}

void SpaceInvader::Start(Renderer* renderer)
{
	Scene::Start(renderer);
	SpaceInvaderPlayer player = SpaceInvaderPlayer();
	player.Start();
}

void SpaceInvader::Update()
{
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
