#include "CollisionManager.h"
#include "Actor.h"
#include "ICollisionListener.h"
#include "ColliderComponent.h"

CollisionManager& CollisionManager::Instance()
{
    static CollisionManager instance;
    return instance;
}

CollisionManager::~CollisionManager()
{

    while (colliders.size() > 0) {
        delete colliders.back();
        colliders.pop_back();
    }
    colliders.clear();
}

void CollisionManager::RegisterCollider(ColliderComponent* collider)
{
    colliders.push_back(collider);
}

void CollisionManager::CheckCollisions()
{
    for (size_t i = 0; i < colliders.size(); ++i) {
        for (size_t j = i + 1; j < colliders.size(); ++j) {
            if (colliders[i]->GetOwner()->GetState() == ActorState::Active && colliders[j]->GetOwner()->GetState() == ActorState::Active) {
                if (colliders[i]->CheckCollisionWith(colliders[j])) {
                    if (colliders[i]->GetIsTriggerable()) {
                        colliders[i]->NotifyListenersStarted();
                    }
                    else {

                    }
                    if (!colliders[j]->GetIsTriggerable()) {

                    }
                    else {

                    }
                }
            }
        }
    }
}
