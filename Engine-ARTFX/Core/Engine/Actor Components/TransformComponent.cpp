#include "TransformComponent.h"
#include "Actor.h"

TransformComponent::TransformComponent(Actor* pOwner, Vector3D position, Vector3D size, Quaternion rotation)
    : mOwner(pOwner), mPosition(position), mSize(size), mRotation(rotation)
{
}

TransformComponent::TransformComponent()
    : mPosition(0), mSize(1), mRotation(0, 0)
{

}

Vector3D TransformComponent::GetPosition()
{
    return mPosition;
}

Vector3D TransformComponent::GetSize()
{
    return mSize;
}

Quaternion TransformComponent::GetRotation()
{
    return mRotation;
}

Matrix4DRow TransformComponent::GetWorldTransform()
{
    return mWorldTransform;
}

void TransformComponent::SetPosition(Vector3D newPosition)
{
    mPosition = newPosition;
    ComputeWorldTransform();
}

void TransformComponent::SetSize(Vector3D newSize)
{
    mSize = newSize;
    ComputeWorldTransform();
}

void TransformComponent::SetRotation(Quaternion newRotation)
{
    mRotation = newRotation;
    ComputeWorldTransform();
}

void TransformComponent::SetOwner(Actor* pOwner)
{
    mOwner = pOwner;
}

void TransformComponent::RotateX(float pAngle)
{
    float piAngle = pAngle * (Maths::PI / 180);
    Quaternion newX({ 1, 0, 0 }, piAngle);
    mRotation = Quaternion::Concatenate(mRotation, newX); 
    ComputeWorldTransform();
}

void TransformComponent::RotateY(float pAngle)
{
    float piAngle = pAngle * (Maths::PI / 180);
    Quaternion newY({ 0, 1, 0 }, piAngle); 
    mRotation = Quaternion::Concatenate(mRotation, newY);
    ComputeWorldTransform(); 
} 

void TransformComponent::RotateZ(float pAngle)
{
    float piAngle = pAngle * (Maths::PI / 180);
    Quaternion newZ({ 0, 0, 1 }, piAngle); 
    mRotation = Quaternion::Concatenate(mRotation, newZ);
    ComputeWorldTransform(); 
}

void TransformComponent::ComputeWorldTransform()
{
    mWorldTransform = Matrix4DRow::CreateScale(mSize);
    mWorldTransform *= Matrix4DRow::CreateFromQuaternion(mRotation);
    mWorldTransform *= Matrix4DRow::CreateTranslation(mPosition);
    mOwner->UpdateComponentsTransform();
}


