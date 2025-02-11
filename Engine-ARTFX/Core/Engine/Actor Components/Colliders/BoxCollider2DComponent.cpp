#include "BoxCollider2DComponent.h"

BoxCollider2DComponent::BoxCollider2DComponent(Actor* owner, int updateOder, Vector2D position, Vector2D size) : ColliderComponent(owner, updateOder), mPosition(position), mSize(size)
{
}

BoxCollider2DComponent::~BoxCollider2DComponent()
{
}

void BoxCollider2DComponent::OnStart()
{
}

void BoxCollider2DComponent::Update()
{

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

void BoxCollider2DComponent::OnCollision()
{

}

bool BoxCollider2DComponent::CheckCollisionWithBox(BoxCollider2DComponent* other)
{
    bool xOverlap = (mPosition.x < other->mPosition.x + other->mSize.x) && (mPosition.x + mSize.x > other->mPosition.x);
    bool yOverlap = (mPosition.y < other->mPosition.y + other->mSize.y) && (mPosition.y + mSize.y > other->mPosition.y);

    return xOverlap && yOverlap;
}

