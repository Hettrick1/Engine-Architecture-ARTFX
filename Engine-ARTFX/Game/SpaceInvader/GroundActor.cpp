#include "GroundActor.h"
#include "Scene.h"
#include "CollisionManager.h"
#include "BoxCollider2DComponent.h"

GroundActor::GroundActor(Vector3D pPos, Vector3D pSize, Quaternion pRotation)
	: Actor(pPos, pSize, pRotation)
{
}

GroundActor::~GroundActor()
{
}

void GroundActor::Start()
{
	Actor::Start();
	Texture* tex = Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/square.png", "ground");
	SpriteComponent* newSprite = new SpriteComponent(this, *tex, 4000);
	AddComponent(newSprite);

	CollisionManager::Instance().CreateCollider<BoxCollider2DComponent>(this, 10, GetTransformComponent().GetSize() * tex->GetTextureSize());
}

void GroundActor::Update()
{
	Actor::Update();
}

void GroundActor::Destroy()
{
	Actor::Destroy();
}

void GroundActor::OnTriggerEnter(ColliderComponent* collider)
{
}

void GroundActor::OnCollision(ColliderComponent* collider)
{
}

void GroundActor::OnTriggerStay(ColliderComponent* collider)
{
}

void GroundActor::OnTriggerExit(ColliderComponent* collider)
{
}
