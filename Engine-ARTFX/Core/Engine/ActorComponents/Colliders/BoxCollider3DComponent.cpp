#include "BoxCollider3DComponent.h"

BoxCollider3DComponent::BoxCollider3DComponent(Actor* pOwner, int pUpdateOder, Vector3D pSize)
    : ColliderComponent(pOwner, pUpdateOder), mShowInGame(true)
{
    mPosition = pOwner->GetTransformComponent().GetPosition();
    mSize = pSize;
}

BoxCollider3DComponent::~BoxCollider3DComponent()
{
}

void BoxCollider3DComponent::OnStart()
{
}

void BoxCollider3DComponent::Update()
{
	mPosition = mOwner->GetTransformComponent().GetPosition();
}

void BoxCollider3DComponent::OnEnd()
{
}

bool BoxCollider3DComponent::CheckCollisionWith(ColliderComponent* other)
{
    if (BoxCollider3DComponent* boxCollider = dynamic_cast<BoxCollider3DComponent*>(other)) {
        if (CheckCollisionWithBox3D(boxCollider)) {
            return true;
        }
        return false;
    }
    return false;
}

bool BoxCollider3DComponent::CheckCollisionWithBox3D(BoxCollider3DComponent* other)
{
    Vector3D minA = mPosition - (mSize * 0.5f); 
    Vector3D maxA = mPosition + (mSize * 0.5f); 
    Vector3D minB = other->mPosition - (other->mSize * 0.5f); 
    Vector3D maxB = other->mPosition + (other->mSize * 0.5f); 

    return (minA.x <= maxB.x && maxA.x >= minB.x) && 
        (minA.y <= maxB.y && maxA.y >= minB.y) && 
        (minA.z <= maxB.z && maxA.z >= minB.z); 
}

void BoxCollider3DComponent::SetShowInGame(bool pShowInGame)
{
}

void BoxCollider3DComponent::SetSize(Vector3D pSize)
{
	mSize = pSize;
}
