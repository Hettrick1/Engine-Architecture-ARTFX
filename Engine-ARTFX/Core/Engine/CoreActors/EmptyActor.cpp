#include "EmptyActor.h"

EmptyActor::EmptyActor(Vector3D pPos, Vector3D pSize, Quaternion pRotation)
	: Actor(pPos, pSize, pRotation)
{
}

EmptyActor::~EmptyActor()
{
}

void EmptyActor::Start()
{
	Actor::Start();
}

void EmptyActor::Update()
{
	Actor::Update();
}

void EmptyActor::Destroy()
{
	Actor::Destroy();
}
