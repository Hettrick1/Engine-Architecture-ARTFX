#pragma once

#include <vector>

class ColliderComponent;

class CollisionManager
{
public:
    static CollisionManager& GetInstance();

    void RegisterCollider(ColliderComponent* collider);

    void CheckCollisions();

private:
    CollisionManager() = default;
    std::vector<ColliderComponent*> colliders;
};

