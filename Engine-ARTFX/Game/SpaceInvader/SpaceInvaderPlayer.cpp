#include "SpaceInvaderPlayer.h"
#include "SpriteComponent.h"
#include "Scene.h"


SpaceInvaderPlayer::SpaceInvaderPlayer() : 
	Actor({500, 500}, 0.5, 0)
{
}

SpaceInvaderPlayer::~SpaceInvaderPlayer()
{
}

void SpaceInvaderPlayer::Start()
{
	Actor::Start();
	Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/pokeball.png", "ball");

	SpriteComponent* sprite = new SpriteComponent(this, Assets::GetTexture("ball"), 500000);
}

void SpaceInvaderPlayer::Update()
{
	Actor::Update();
}

void SpaceInvaderPlayer::Destroy()
{
	Actor::Destroy();
}
