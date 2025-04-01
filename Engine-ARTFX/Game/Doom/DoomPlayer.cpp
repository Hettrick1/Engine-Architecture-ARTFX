#include "DoomPlayer.h"
#include "DoomPC.h"
#include "CameraComponent.h"
#include "RigidbodyComponent.h"
#include "SpriteComponent.h"
#include "Assets.h"
#include "Scene.h"
#include "MeshComponent.h"
#include "Timer.h"

DoomPlayer::DoomPlayer()
	: Actor(), mGun(nullptr)
{
}

DoomPlayer::~DoomPlayer()
{
}

void DoomPlayer::Start()
{
	Actor::Start();
	RigidbodyComponent* rigidBody = new RigidbodyComponent(this);
	SetRigidBody(rigidBody);
	DoomPC* playerController = new DoomPC(this, 1);
	AddComponent(playerController);
	Texture* tex3 = Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/WalkAnim/Walk1.png", "walk1");

	std::vector<Texture*> gunAnim = {
		Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/Doom/gun1.png", "gun1"),
		Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/Doom/gun2.png", "gun2"),
		Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/Doom/gun3.png", "gun3"),
		Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/Doom/gun4.png", "gun4")
	};

	CameraComponent* cameraComponent = new CameraComponent(this);
	cameraComponent->SetRelativePosition(Vector3D(0, 0, 0));
	AddComponent(cameraComponent);
	mGun = new FlipbookComponent(this, gunAnim, 10);
	mGun->SetRelativePosition(Vector3D(0, 2, -0.5));
	mGun->RelativeRotateX(90);
	mGun->SetAnimationFps(8);
	AddComponent(mGun);
}

void DoomPlayer::Update()
{
	Actor::Update();
	Vector3D bobbing = mGun->GetRelativePosition();
	if (GetRigidBody()->GetVelocity().LengthSq() > 0) {
		float time = SDL_GetTicks() * 0.01f;

		bobbing.z -= Maths::Sin(time) * 0.005f;

		bobbing.x += Maths::Sin(time * 0.5) * 0.005f;

		mGun->SetRelativePosition(bobbing);
	}
	else 
	{
		float lerpRelativeSpeed = 8;
		Vector3D lerpRelative = Vector3D::Lerp(mGun->GetRelativePosition(), Vector3D(0, 2, -0.5), Timer::deltaTime * lerpRelativeSpeed);
		mGun->SetRelativePosition(lerpRelative);
	}
}

void DoomPlayer::Destroy()
{
}
