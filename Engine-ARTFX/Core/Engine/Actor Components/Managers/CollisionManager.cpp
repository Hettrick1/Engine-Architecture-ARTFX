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
    /*for (size_t i = 0; i < colliders.size()-1; ++i) {
        for (size_t j = i + 1; j < colliders.size(); ++j) {
            if (colliders[i]->GetOwner()->GetState() == ActorState::Active && colliders[j]->GetOwner()->GetState() == ActorState::Active) {
                if (colliders[i]->CheckCollisionWith(colliders[j])) {
                    if (colliders[i]->GetIsTriggerable()) {
                        colliders[i]->SetHitResult(true, colliders[j]->GetOwner());
                        colliders[j]->SetHitResult(true, colliders[i]->GetOwner());
                        colliders[i]->NotifyListenersStarted();
                        colliders[j]->NotifyListenersStarted();
                    }
                    else {

                    }
                    if (!colliders[j]->GetIsTriggerable()) {

                    }
                    else {

                    }
                }
                else {
                    colliders[i]->SetHitResult(false, nullptr);
                    colliders[j]->SetHitResult(false, nullptr);
                }
            }
        }
    }*/
    std::vector<ColliderComponent*> activeColliders;
    for (auto& collider : colliders) {
        if (collider->GetOwner()->GetState() == ActorState::Active) {
            activeColliders.push_back(collider);
        }
    }

    for (size_t i = 0; i < activeColliders.size() - 1; ++i) {
        for (size_t j = i + 1; j < activeColliders.size(); ++j) {
            auto* collider1 = activeColliders[i];
            auto* collider2 = activeColliders[j];

            if (collider1->CheckCollisionWith(collider2)) {
                if (collider1->GetIsTriggerable()) {
                    collider1->SetHitResult(true, collider2->GetOwner());
                    collider1->NotifyListenersStarted();
                }
                if (collider2->GetIsTriggerable()) {
                    collider2->SetHitResult(true, collider1->GetOwner());
                    collider2->NotifyListenersStarted();
                }
            }
            else {
                collider1->SetHitResult(false, nullptr);
                collider2->SetHitResult(false, nullptr);
            }
        }
    }
}
