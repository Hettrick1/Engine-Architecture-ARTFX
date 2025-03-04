#include "CameraActor.h"
#include "PlayerController3D.h"
#include "CameraComponent.h"

CameraActor::CameraActor()
	: Actor()
{
}

CameraActor::~CameraActor()
{
}

void CameraActor::Start()
{
	Actor::Start();
	CameraComponent* cc = new CameraComponent(this);
	AddComponent(cc);
	PlayerController3D* pc = new PlayerController3D(this, 100);
	pc->SetMovementSpeed(5);
	AddComponent(pc); 
}

void CameraActor::Update()
{
	Actor::Update();
}

void CameraActor::Destroy()
{
	Actor::Destroy();
}
