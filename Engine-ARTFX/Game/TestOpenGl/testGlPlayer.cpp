#include "testGlPlayer.h"
#include "Scene.h"
#include "BooleanActions.h"
#include "InputManager.h"
#include "PlayerController2D.h"
#include "Physics/CollisionManager.h"
#include "BoxCollider2DComponent.h"


testGlPlayer::testGlPlayer() :
	Actor()
{
}

testGlPlayer::~testGlPlayer()
{
}

void testGlPlayer::Start()
{
	Actor::Start();
	Texture* walkAnimTextures = Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/WalkAnim/Walk1.png", "walk1");
		
	SpriteComponent* walkAnim = new SpriteComponent(this, *walkAnimTextures, 500000);
	AddComponent(walkAnim);

	mTransformComponent.RotateZ(45);
}

void testGlPlayer::Update()
{
	Actor::Update();
}

void testGlPlayer::Destroy()
{
	Actor::Destroy();
}



