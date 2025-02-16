#include "Actor.h"
#include "Component.h"
#include "Scene.h"
#include <algorithm>

Actor::Actor(Vector2D position, Vector2D size, float rotation) : 
    mState(ActorState::Active), mScene(*Scene::ActiveScene)
{
    mTransformComponent.SetPosition(position);
    mTransformComponent.SetSize(size);
    mTransformComponent.SetRotation(rotation);
}

Actor::~Actor()
{
}

void Actor::Start()
{
}

void Actor::AttachScene(Scene& scene)
{
    mScene = scene;
}

void Actor::AddComponent(Component* component)
{
    if (mIsUpdatingComponents) 
    {
        mPendingComponents.emplace_back(component);
    }
    else 
    {
        mComponents.emplace_back(component);
    }
}

void Actor::RemoveComponent(Component* component)
{
    std::vector<Component*>::iterator it = find(mPendingComponents.begin(), mPendingComponents.end(), component);
    if (it != mPendingComponents.end())
    {
        iter_swap(it, mPendingComponents.end() - 1);
        mPendingComponents.pop_back();
    }
    it = find(mComponents.begin(), mComponents.end(), component);
    if (it != mComponents.end())
    {
        iter_swap(it, mComponents.end() - 1);
        mComponents.pop_back();
    }
}

void Actor::SetActive(ActorState state)
{
    mState = state;
}

void Actor::SetPosition(Vector2D pPosition)
{
    mTransformComponent.SetPosition(pPosition);
}

void Actor::Update()
{
    mIsUpdatingComponents = true;
    for (Component* component : mComponents)
    {
        component->Update();
    }
    mIsUpdatingComponents = false;
    for (Component* component : mPendingComponents)
    {
        mComponents.emplace_back(component);
    }
    mPendingComponents.clear();
}

void Actor::Destroy()
{
    while (!mComponents.empty()) {
        delete mComponents.back();
    }
    while (!mPendingComponents.empty()) {
        delete mPendingComponents.back();
    }
}

std::vector<Component*> Actor::GetComponents() const
{
    return mComponents;
}

ActorState Actor::GetState()
{
    return mState;
}

Scene& Actor::GetScene()
{
    return mScene;
}

Transform2D& Actor::GetTransformComponent()
{
    return mTransformComponent;
}