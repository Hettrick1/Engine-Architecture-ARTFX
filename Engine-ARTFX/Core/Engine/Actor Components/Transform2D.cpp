#include "Transform2D.h"

Transform2D::Transform2D(Vector2D position, Vector2D size, float rotation)
    : mPosition(position), mSize(size), mRotation(rotation)
{
}

Transform2D::Transform2D()
    : mPosition(0), mSize(1), mRotation(0)
{

}

Vector2D Transform2D::GetPosition()
{
    return mPosition;
}

Vector2D Transform2D::GetSize()
{
    return mSize;
}

float Transform2D::GetRotation()
{
    return mRotation;
}

void Transform2D::SetPosition(Vector2D newPosition)
{
    mPosition = newPosition;
}

void Transform2D::SetSize(Vector2D newSize)
{
    mSize = newSize;
}

void Transform2D::SetRotation(float newRotation)
{
    mRotation = newRotation;
}


