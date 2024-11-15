#pragma once

#include <vector>

class Collider;

class CollisionManager
{
public:
    static CollisionManager& GetInstance();

    void RegisterCollider(Collider* collider);

    void CheckCollisions();

private:
    CollisionManager() = default;
    std::vector<Collider*> colliders;
};

