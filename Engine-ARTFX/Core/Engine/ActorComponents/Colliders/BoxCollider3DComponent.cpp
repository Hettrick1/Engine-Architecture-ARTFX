#include "BoxCollider3DComponent.h"
#include <algorithm>

BoxCollider3DComponent::BoxCollider3DComponent(Actor* pOwner, int pUpdateOder, Vector3D pSize)
    : ColliderComponent(pOwner, pUpdateOder), mShowInGame(true)
{
    pOwner->AddComponent(this);
    mPosition = pOwner->GetTransformComponent().GetPosition();
    mLastPosition = mPosition;
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
    ColliderComponent::Update();
    mLastPosition = mPosition;
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
    mLastPosition = mPosition;
    mPosition = mOwner->GetTransformComponent().GetPosition();
    Vector3D delta = mPosition - mLastPosition;
    Vector3D predictedPosition = mLastPosition;

    Vector3D otherDelta = other->GetOwner()->GetTransformComponent().GetPosition() - other->GetLastPosition();
    Vector3D otherPredictedPosition = other->GetLastPosition();

    // Calculer un pas adaptatif basé sur la vitesse des objets
    float maxDelta = std::max(delta.Length(), otherDelta.Length());
    float stepSize = maxDelta > 0 ? std::min(0.001f, 0.5f / maxDelta) : 0.001f;

    float step = 0.0;
    while (step < 1.0f)
    {
        predictedPosition = mLastPosition + delta * step;
        otherPredictedPosition = other->GetLastPosition() + otherDelta * step;

        Vector3D minA = predictedPosition - (mSize * 0.5f);
        Vector3D maxA = predictedPosition + (mSize * 0.5f);
        Vector3D minB = otherPredictedPosition - (other->mSize * 0.5f);
        Vector3D maxB = otherPredictedPosition + (other->mSize * 0.5f);

        if ((minA.x <= maxB.x && maxA.x >= minB.x) &&
            (minA.y <= maxB.y && maxA.y >= minB.y) &&
            (minA.z <= maxB.z && maxA.z >= minB.z))
        {
            // Stockez les positions au moment exact de la collision
            mCollisionPosition.first = predictedPosition;
            mCollisionPosition.second = otherPredictedPosition;
            return true;
        }
        step += stepSize;
    }

    mCollisionPosition.first = 0;
    mCollisionPosition.second = 0;
    mLastPosition = mPosition;
    return false;
}

void BoxCollider3DComponent::SetShowInGame(bool pShowInGame)
{
}

void BoxCollider3DComponent::SetSize(Vector3D pSize)
{
	mSize = pSize;
}

Vector3D BoxCollider3DComponent::GetLastPosition()
{
    return mLastPosition;
}
