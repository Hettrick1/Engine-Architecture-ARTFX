#include "SpaceInvaderPlayer.h"
#include "Scene.h"
#include "BooleanActions.h"
#include "InputManager.h"
#include "PlayerController.h"
#include "CollisionManager.h"
#include "BoxCollider2DComponent.h"


SpaceInvaderPlayer::SpaceInvaderPlayer() :
	Actor({ 500, 500 }, 1.0, 0)
{
}

SpaceInvaderPlayer::~SpaceInvaderPlayer()
{
}

void SpaceInvaderPlayer::Start()
{
	Actor::Start();
	std::vector<Texture*> walkAnimTextures = {
		Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/WalkAnim/Walk1.png", "walk1"),
		Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/WalkAnim/Walk2.png", "walk2"),
		Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/WalkAnim/Walk3.png", "walk3"),
		Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/WalkAnim/Walk4.png", "walk4"),
		Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/WalkAnim/Walk5.png", "walk5")
	};
	CollisionManager::Instance().CreateCollider<BoxCollider2DComponent>(this, 10, GetTransformComponent().GetSize() * 64);

	Texture* tex = Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/collider64x64.png", "ground");
	SpriteComponent* newSprite = new SpriteComponent(this, *tex, 4000);
	AddComponent(newSprite);

	FlipbookComponent* walkAnim = new FlipbookComponent(this, walkAnimTextures, 500000);
	walkAnim->SetAnimationFps(5);
	AddComponent(walkAnim);

	PlayerController* pc = new PlayerController(this, 100); 
	AddComponent(pc);
}

void SpaceInvaderPlayer::Update()
{
	Actor::Update();
}

void SpaceInvaderPlayer::Destroy()
{
	Actor::Destroy();
}

void SpaceInvaderPlayer::OnTriggerEnter(ColliderComponent* collider)
{
    PlayerController* pc = GetComponentOfType<PlayerController>();
    Actor* otherActor = collider->GetHitResult().hitActor;

    float playerX = GetTransformComponent().GetPosition().x;
    float playerY = GetTransformComponent().GetPosition().y;
    float otherX = otherActor->GetTransformComponent().GetPosition().x;
    float otherY = otherActor->GetTransformComponent().GetPosition().y;

	float distX = Maths::Abs(playerX - otherX);
	float distY = Maths::Abs(playerY - otherY);

	if (distX > distY) {
		pc->SetSpeedY(0);
	}
	else {
		pc->SetSpeedX(0);
	}
}

void SpaceInvaderPlayer::OnCollision(ColliderComponent* collider)
{
}

void SpaceInvaderPlayer::OnTriggerStay(ColliderComponent* collider)
{
}

void SpaceInvaderPlayer::OnTriggerExit(ColliderComponent* collider)
{
}


