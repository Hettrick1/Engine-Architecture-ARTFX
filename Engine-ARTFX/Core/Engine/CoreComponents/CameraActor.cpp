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
}

void CameraActor::Update()
{
	Actor::Update();
}

void CameraActor::Destroy()
{
	Actor::Destroy();
}
