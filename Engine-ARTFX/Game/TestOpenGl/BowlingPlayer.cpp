#include "BowlingPlayer.h"
#include "PlayerController3D.h"
#include "CameraComponent.h"

BowlingPlayer::BowlingPlayer()
	: Actor()
{
}

BowlingPlayer::~BowlingPlayer()
{
}

void BowlingPlayer::Start()
{
	Actor::Start();
	CameraComponent* cc = new CameraComponent(this);
	AddComponent(cc);
	PlayerController3D* pc = new PlayerController3D(this, 100);
	pc->SetMovementSpeed(5);
	AddComponent(pc);
}

void BowlingPlayer::Update()
{
	Actor::Update();
}

void BowlingPlayer::Destroy()
{
	Actor:Destroy();
}
