#include "CollisionManager.h"

CollisionManager& CollisionManager::GetInstance()
{
    static CollisionManager instance;
    return instance;
}

void CollisionManager::RegisterCollider(Collider* collider)
{
    colliders.push_back(collider);
}

void CollisionManager::CheckCollisions()
{
    for (size_t i = 0; i < colliders.size(); ++i) {
        for (size_t j = i + 1; j < colliders.size(); ++j) {
            if (colliders[i]->GetOwner()->GetState() == ActorState::Active && colliders[j]->GetOwner()->GetState() == ActorState::Active) {
                if (colliders[i]->CheckCollisionWith(colliders[j])) {
                    if (!colliders[i]->GetIsTriggerable()) {
                        colliders[i]->OnCollision();
                    }
                    else {
                        colliders[i]->OnTriggerEnter();
                    }
                    if (!colliders[j]->GetIsTriggerable()) {
                        colliders[j]->OnCollision();
                    }
                    else {
                        colliders[j]->OnTriggerEnter();
                    }
                }
            }
        }
    }
}
