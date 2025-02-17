#pragma once

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

    ColliderType* newCollider = new ColliderType(std::forward<Args>(args)...);

    newCollider->AddListener(pListener);

    RegisterCollider(newCollider);
}

