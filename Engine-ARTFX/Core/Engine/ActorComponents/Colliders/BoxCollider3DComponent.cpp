#include "BoxCollider3DComponent.h"
#include "MeshComponent.h"
#include "IRenderer.h"
#include "Assets.h"
#include <algorithm>
#include <iostream>

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
    Vector3D otherDelta = other->GetOwner()->GetTransformComponent().GetPosition() - other->GetLastPosition();

    float maxDelta = std::max(delta.Length(), otherDelta.Length());
    int steps = std::max(1, static_cast<int>(maxDelta / 0.05f));
    float stepSize = 1.0f / steps;

    for (int i = 0; i <= steps; i++)
    {
        float t = i * stepSize;
        Vector3D predictedPosition = mLastPosition + delta * t;
        Vector3D otherPredictedPosition = other->GetLastPosition() + otherDelta * t;

        Vector3D minA = predictedPosition - (mSize);
        Vector3D maxA = predictedPosition + (mSize);
        Vector3D minB = otherPredictedPosition - (other->mSize);
        Vector3D maxB = otherPredictedPosition + (other->mSize);

        if ((minA.x <= maxB.x && maxA.x >= minB.x) &&
            (minA.y <= maxB.y && maxA.y >= minB.y) &&
            (minA.z <= maxB.z && maxA.z >= minB.z))
        {
            mCollisionPosition.first = predictedPosition;
            mCollisionPosition.second = otherPredictedPosition;
            return true;
        }
    }

    // Pas de collision, reset des valeurs
    mCollisionPosition.first = Vector3D(0, 0, 0);
    mCollisionPosition.second = Vector3D(0, 0, 0);
    return false;
}

void BoxCollider3DComponent::SetShowInGame(bool pShowInGame)
{
}

void BoxCollider3DComponent::SetSize(Vector3D pSize)
{
	mSize = pSize;
}

void BoxCollider3DComponent::DebugDraw(IRenderer& renderer)
{
    Vector3D min = mPosition - mSize;
    Vector3D max = mPosition + mSize;
    Matrix4DRow wt;

    wt = Matrix4DRow::CreateScale(mSize * 2);
    wt *= Matrix4DRow::CreateTranslation(mPosition);

    renderer.DrawDebugBox(min, max, wt);
}

Vector3D BoxCollider3DComponent::GetLastPosition()
{
    return mLastPosition;
}
