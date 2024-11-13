#include "BoxCollider2D.h"

BoxCollider2D::BoxCollider2D(Actor* owner, int updateOder, Vector2D position, Vector2D size) : Collider(owner, updateOder), mPosition(position), mSize(size)
{
}

BoxCollider2D::~BoxCollider2D()
{
}

void BoxCollider2D::OnStart()
{
}

void BoxCollider2D::Update()
{

}

void BoxCollider2D::OnEnd()
{
}

void BoxCollider2D::CheckCollisionWith(Collider* other)
{
    if (BoxCollider2D* boxCollider = dynamic_cast<BoxCollider2D*>(other)) {
        if (CheckCollisionWithBox(boxCollider)) {
            OnCollision();  
        }
    }
}

void BoxCollider2D::OnCollision()
{

}

bool BoxCollider2D::CheckCollisionWithBox(BoxCollider2D* other)
{
    bool xOverlap = (mPosition.x < other->mPosition.x + other->mSize.x) && (mPosition.x + mSize.x > other->mPosition.x);
    bool yOverlap = (mPosition.y < other->mPosition.y + other->mSize.y) && (mPosition.y + mSize.y > other->mPosition.y);

    return xOverlap && yOverlap;
}

