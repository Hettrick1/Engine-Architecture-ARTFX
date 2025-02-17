#include "BoxCollider2DComponent.h"
#include "SpriteComponent.h"
#include "Scene.h"
#include "Actor.h"

BoxCollider2DComponent::BoxCollider2DComponent(Actor* pOwner, int pUpdateOder, Vector2D pSize) 
    : ColliderComponent(pOwner, pUpdateOder), mSize(pSize), mShowInGame(true)
{
    mPosition = pOwner->GetTransformComponent().GetPosition();
    if (mShowInGame) {
        Texture* tex = Assets::LoadTexture(*mOwner->GetScene().GetRenderer(), "Imports/Sprites/collider.png", "ground");
        SpriteComponent* newSprite = new SpriteComponent(mOwner, *tex, 4000);
        mOwner->AddComponent(newSprite);
    }
}

BoxCollider2DComponent::~BoxCollider2DComponent()
{
}

void BoxCollider2DComponent::OnStart()
{
}

void BoxCollider2DComponent::Update()
{
    mPosition = mOwner->GetTransformComponent().GetPosition();
}

void BoxCollider2DComponent::OnEnd()
{
}

bool BoxCollider2DComponent::CheckCollisionWith(ColliderComponent* other)
{
    if (BoxCollider2DComponent* boxCollider = dynamic_cast<BoxCollider2DComponent*>(other)) {
        if (CheckCollisionWithBox(boxCollider)) {
            return true;
        }
        return false;
    }
    return false;
}

bool BoxCollider2DComponent::CheckCollisionWithBox(BoxCollider2DComponent* other)
{
    bool xOverlap = (mPosition.x < other->mPosition.x + other->mSize.x) && (mPosition.x + mSize.x > other->mPosition.x);
    bool yOverlap = (mPosition.y < other->mPosition.y + other->mSize.y) && (mPosition.y + mSize.y > other->mPosition.y);

    return xOverlap && yOverlap;
}

void BoxCollider2DComponent::SetShowInGame(bool showInGame)
{
    mShowInGame = showInGame;
}

void BoxCollider2DComponent::SetSize(Vector2D pSize)
{
    mSize = pSize;
}

