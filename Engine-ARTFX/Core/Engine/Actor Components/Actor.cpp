#include "Actor.h"
#include "Component.h"
#include "../../Scenes/Scene.h"

Actor::Actor(Vector2D position, Vector2D size, float rotation) : 
    mState(ActorState::Active), mTransformComponent({ position, size, rotation }), mScene(*Scene::ActiveScene)
{

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
}

void Actor::RemoveComponent(int index)
{
}

void Actor::SetActive(bool active)
{
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

Transform2DComponent& Actor::GetTransformComponent()
{
    return mTransformComponent;
}

void Actor::Update()
{
}

void Actor::Destroy()
{
}
