#include "DoomPlayer.h"
#include "DoomPC.h"
#include "CameraComponent.h"
#include "RigidbodyComponent.h"
#include "SpriteComponent.h"
#include "Assets.h"
#include "Scene.h"
#include "MeshComponent.h"
#include "Timer.h"
#include "TextRenderer.h"
#include "HudManager.h"
#include "Physics/CollisionManager.h"
#include "Physics/PhysicManager.h"

float bobingTime = 0;

DoomPlayer::DoomPlayer()
	: Actor(), mGun(nullptr), mGunAmo(50), mHealth(100), mArmor(100), 
	mFpsText(nullptr), mGunAmoText(nullptr), mHealthText(nullptr), mArmorText(nullptr), 
	mWeaponIconImage(nullptr), mWeapon(Weapons::Gun)
{
}

DoomPlayer::~DoomPlayer()
{
	delete mGun;
	delete mFpsText;
	delete mGunAmoText;
	delete mHealthText;
	delete mArmorText;
	delete mWeaponIconImage;
}

void DoomPlayer::Start()
{
	Actor::Start();
	RigidbodyComponent* rigidBody = new RigidbodyComponent(this);
	SetRigidBody(rigidBody);
	DoomPC* playerController = new DoomPC(this, 1);
	playerController->SetPlayerRef(this);
	AddComponent(playerController);
	Texture* doomHud = Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/Doom/DoomHud.png", "doomHud");
	gunIcon = *Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/Doom/DoomHudGunIcon.png", "gunIcon");
	shotgunIcon = *Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/Doom/DoomHudShotGunIcon.png", "shotgunIcon");

	mGunAnim = {
		Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/Doom/gun1.png", "gun1"),
		Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/Doom/gun2.png", "gun2"),
		Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/Doom/gun3.png", "gun3"),
		Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/Doom/gun4.png", "gun4")
	};
	mShotgunAnim = {
		Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/Doom/shotgun1.png", "shotgun1"),
		Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/Doom/shotgun2.png", "shotgun2"),
		Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/Doom/shotgun3.png", "shotgun3"),
		Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/Doom/shotgun4.png", "shotgun4"),
		Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/Doom/shotgun5.png", "shotgun5"),
		Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/Doom/shotgun6.png", "shotgun6")
	};

	CameraComponent* cameraComponent = new CameraComponent(this);
	cameraComponent->SetRelativePosition(Vector3D::zero);
	AddComponent(cameraComponent);
	mGun = new FlipbookComponent(this, mGunAnim, 10);
	mGun->SetRelativePosition(Vector3D(0.0f, 2.0f, -0.2f));
	mGun->RelativeRotateX(90);
	mGun->SetAnimationFps(8);
	mGun->SetCullOff(true);
	AddComponent(mGun);
	 
	mFpsText = new HudText("AAAAAAAAA", -1900, 1000, 0.5f, Vector3D(1, 0, 1));
	mGunAmoText = new HudText(std::to_string(mGunAmo), -825, -930, 1, Vector3D(0.7f, 0, 0), TextAlignment::CENTER);
	mHealthText = new HudText(std::to_string(mHealth), -325, -930, 1, Vector3D(0.7f, 0, 0), TextAlignment::CENTER);
	mArmorText = new HudText(std::to_string(mArmor), 840, -930, 1, Vector3D(0.7f, 0, 0), TextAlignment::CENTER);;
	HudImage* doomHudImage = new HudImage(*doomHud, Vector2D(0, -920), Vector2D(10, 10));
	mWeaponIconImage = new HudImage(gunIcon, Vector2D(400, -980), Vector2D(10, 10));

	GetScene().GetRenderer()->GetHud()->AddElement(doomHudImage); 
	GetScene().GetRenderer()->GetHud()->AddElement(mWeaponIconImage);
	GetScene().GetRenderer()->GetHud()->AddElement(mFpsText);
	GetScene().GetRenderer()->GetHud()->AddElement(mGunAmoText);
	GetScene().GetRenderer()->GetHud()->AddElement(mHealthText);
	GetScene().GetRenderer()->GetHud()->AddElement(mArmorText);
}

void DoomPlayer::Update()
{
	Actor::Update();
	Vector3D bobbing = mGun->GetRelativePosition();
	if (GetRigidBody()->GetVelocity().LengthSq() > 0) {

		bobingTime += Timer::deltaTime * 10.0f;

		bobbing.z -= Maths::Sin(bobingTime) * 0.005f;

		bobbing.x += Maths::Sin(bobingTime * 0.5f) * 0.005f;

		mGun->SetRelativePosition(bobbing);
	}
	else 
	{
		float lerpRelativeSpeed = 8;
		Vector3D lerpRelative = Vector3D::Lerp(mGun->GetRelativePosition(), Vector3D(0.0f, 2.0f, -0.2f), Timer::deltaTime * lerpRelativeSpeed);
		mGun->SetRelativePosition(lerpRelative);
		bobingTime = 0;
	}
	mFpsText->SetText("Fps : " + std::to_string(Timer::mFPS));

	// Lancer un rayon
	Vector3D start = GetTransformComponent().GetPosition();
	start.z += 0;
	Vector3D end = start + GetTransformComponent().GetWorldTransform().GetYAxis() * 2;
	HitResult hit;
	if (PhysicManager::Instance().LineTrace(start, end, hit))
	{
		std::cout << "Ray hit at: " << hit.HitPoint.x << ", " << hit.HitPoint.y << ", " << hit.HitPoint.z << std::endl;
	}
	else
	{
		std::cout << "No hit" << std::endl;
	}
	Line* line = new Line(start, end, hit);
	GetScene().GetRenderer()->AddDebugLine(line);
}

void DoomPlayer::Destroy()
{
}

Actor* DoomPlayer::GetActorRef()
{
	return static_cast<Actor*>(this);
}

void DoomPlayer::ChangeWeapon()
{
	if (mWeapon == Weapons::Gun)
	{
		mWeapon = Weapons::Shotgun;
	}
	else
	{
		mWeapon = Weapons::Gun;
	}
	switch (mWeapon) {
	case Weapons::Gun :
		mGun->SetAnimationFps(8);
		mGun->SetAnimationTextures(mGunAnim);
		mWeaponIconImage->SetTexture(gunIcon);
		break;
	case Weapons::Shotgun:
		mGun->SetAnimationFps(8);
		mGun->SetAnimationTextures(mShotgunAnim);
		mWeaponIconImage->SetTexture(shotgunIcon);
		break;
	}
}
