#pragma once
#include "Log.h"
#include "Actor.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>

// Collision Manager Class to handle all the collision check and to send all the event related to collisons

class ColliderComponent;
class ICollisionListener;

class CollisionManager
{
public:
    static CollisionManager& Instance();
    ~CollisionManager();

    void RegisterCollider(ColliderComponent* pCollider);

    void CheckCollisions();

    template <typename ColliderType, typename... Args>
    void CreateCollider(ICollisionListener* pListener, Args&&... args);

private:
    CollisionManager() = default;
    std::vector<ColliderComponent*> mAllColliders;
    std::unordered_map<ColliderComponent*, std::unordered_set<ColliderComponent*>> mCurrentCollisions;
};

// template to create the collider of the type needed 

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

struct CollisionPairHash { // hash to handle collision pair, to send only one OnTriggerEnd event
    std::size_t operator()(const std::pair<ColliderComponent*, ColliderComponent*>& pair) const {
        auto h1 = std::hash<ColliderComponent*>{}(pair.first);
        auto h2 = std::hash<ColliderComponent*>{}(pair.second);
        return h1 ^ (h2 << 1); // XOR to minimize hash collisions
    }
};
