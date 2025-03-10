#include "BoxCollider3DComponent.h"

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
    mPosition = mOwner->GetTransformComponent().GetPosition();
    Vector3D delta = mPosition - mLastPosition;
    Vector3D predictedPosition = mLastPosition;

    Vector3D otherDelta = other->GetOwner()->GetTransformComponent().GetPosition() - other->GetLastPosition();
    Vector3D otherPredictedPosition = other->GetLastPosition();

    float step = 0.0;

    while (step < 1.0f)
    {
        predictedPosition = mLastPosition + delta * step;
        otherPredictedPosition = other->GetLastPosition() + otherDelta * step;

        //Log::Info(std::to_string(predictedPosition.z));

        Vector3D minA = predictedPosition - (mSize * 0.5f);
        Vector3D maxA = predictedPosition + (mSize * 0.5f);
        Vector3D minB = otherPredictedPosition - (other->mSize * 0.5f);
        Vector3D maxB = otherPredictedPosition + (other->mSize * 0.5f);

        if ((minA.x <= maxB.x && maxA.x >= minB.x) &&
            (minA.y <= maxB.y && maxA.y >= minB.y) &&
            (minA.z <= maxB.z && maxA.z >= minB.z))
        {
            return true;
        }
        step += 0.001f;
    }
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
