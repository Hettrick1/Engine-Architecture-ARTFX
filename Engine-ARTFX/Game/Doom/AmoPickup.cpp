#include "AmoPickup.h"
#include "Assets.h"
#include "SpriteComponent.h"
#include "BoxCollider3DComponent.h"
#include "Scene.h"

AmoPickup::AmoPickup(Vector3D pPos, Vector3D pSize, Quaternion pRotation)
	:Actor(pPos, pSize, pRotation)
{
}

AmoPickup::~AmoPickup()
{
}

void AmoPickup::Start()
{
	Actor::Start();
	Texture* tex = Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/planks.png", "cube");
	SpriteComponent* sc = new SpriteComponent(this, *tex);
	sc->RelativeRotateX(90);
	BoxCollider3DComponent* bc = new BoxCollider3DComponent(this, 10, 0.5);
	bc->SetIsQuerry(true);
	bc->AddListener(this);
}

void AmoPickup::Update()
{
	Actor::Update();
}

void AmoPickup::Destroy()
{
	Actor::Destroy();
}

void AmoPickup::OnTriggerEnter(ColliderComponent* collider)
{
	SetActive(ActorState::Paused);
	Log::Info("OUIIIIIIIIIIIIIII");
}

void AmoPickup::OnCollision(ColliderComponent* collider)
{
}

void AmoPickup::OnTriggerStay(ColliderComponent* collider)
{
}

void AmoPickup::OnTriggerExit(ColliderComponent* collider)
{
}
