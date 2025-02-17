#pragma once
#include "Log.h"
#include "Actor.h"
#include <vector>

class ColliderComponent;
class ICollisionListener;

class CollisionManager
{
public:
    static CollisionManager& Instance();
    ~CollisionManager();

    void RegisterCollider(ColliderComponent* collider);

    void CheckCollisions();

    template <typename ColliderType, typename... Args>
    void CreateCollider(ICollisionListener* pListener, Args&&... args);

private:
    CollisionManager() = default;
    std::vector<ColliderComponent*> colliders;
};

template<typename ColliderType, typename ...Args>
inline void CollisionManager::CreateCollider(ICollisionListener* pListener, Args && ...args)
{
    static_assert(std::is_base_of<ColliderComponent, ColliderType>::value,
        "ColliderType must be derived from ColliderComponent!");
    Actor* owner = dynamic_cast<Actor*>(pListener);
    if (owner == nullptr) {
        Log::Error(LogType::Application, "owner does not derive from actor!");
        return;
    }

    ColliderType* newCollider = new ColliderType(owner, std::forward<Args>(args)...);
    owner->AddComponent(newCollider);

    newCollider->AddListener(pListener);

    RegisterCollider(newCollider);
}

