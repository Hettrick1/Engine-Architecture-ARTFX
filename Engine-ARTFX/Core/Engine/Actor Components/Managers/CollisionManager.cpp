#include "CollisionManager.h"
#include "Actor.h"
#include "ICollisionListener.h"
#include "ColliderComponent.h"
#include <utility>
#include <algorithm>

CollisionManager& CollisionManager::Instance()
{
    static CollisionManager instance;
    return instance;
}

CollisionManager::~CollisionManager()
{

    while (mAllColliders.size() > 0) {
        delete mAllColliders.back();
        mAllColliders.pop_back();
    }
    mAllColliders.clear();
}

void CollisionManager::RegisterCollider(ColliderComponent* pCollider)
{
    mAllColliders.push_back(pCollider);
}

void CollisionManager::CheckCollisions()
{
    std::vector<ColliderComponent*> activeColliders;
    for (auto& collider : mAllColliders) {
        if (collider->GetOwner()->GetState() == ActorState::Active) {
            activeColliders.push_back(collider);
        }
    }

    std::unordered_map<ColliderComponent*, std::unordered_set<ColliderComponent*>> newCollisions;

    for (size_t i = 0; i < activeColliders.size() - 1; ++i) {
        for (size_t j = i + 1; j < activeColliders.size(); ++j) {
            auto* collider1 = activeColliders[i];
            auto* collider2 = activeColliders[j];

            if (collider1->CheckCollisionWith(collider2)) {
                bool isNewCollision1 = mCurrentCollisions[collider1].find(collider2) == mCurrentCollisions[collider1].end();
                bool isNewCollision2 = mCurrentCollisions[collider2].find(collider1) == mCurrentCollisions[collider2].end();

                if (isNewCollision1) {
                    if (collider1->GetIsTriggerable()) {
                        collider1->SetHitResult(true, collider2->GetOwner());
                        collider1->NotifyListenersStarted();
                    }
                }
                else {
                    if (collider1->GetIsTriggerable()) {
                        collider1->NotifyListenersStay();
                    }
                }

                if (isNewCollision2) {
                    if (collider2->GetIsTriggerable()) {
                        collider2->SetHitResult(true, collider1->GetOwner());
                        collider2->NotifyListenersStarted();
                    }
                }
                else {
                    if (collider2->GetIsTriggerable()) {
                        collider2->NotifyListenersStay();
                    }
                }

                newCollisions[collider1].insert(collider2);
                newCollisions[collider2].insert(collider1);
            }
        }
    }

    std::unordered_set<std::pair<ColliderComponent*, ColliderComponent*>, CollisionPairHash> processedCollisions;

    for (auto& pair : mCurrentCollisions) {
        ColliderComponent* collider = pair.first;
        std::unordered_set<ColliderComponent*>& previousCollisions = pair.second;

        for (auto* otherCollider : previousCollisions) {
            if (newCollisions[collider].find(otherCollider) == newCollisions[collider].end()) {
                std::pair<ColliderComponent*, ColliderComponent*> collisionPair =
                    std::minmax(collider, otherCollider);

                if (processedCollisions.find(collisionPair) == processedCollisions.end()) {
                    processedCollisions.insert(collisionPair);

                    if (collider->GetIsTriggerable()) {
                        collider->NotifyListenersEnded();
                    }
                    if (otherCollider->GetIsTriggerable()) {
                        otherCollider->NotifyListenersEnded();
                    }

                    collider->SetHitResult(false, nullptr);
                    otherCollider->SetHitResult(false, nullptr);
                }
            }
        }
    }
    mCurrentCollisions = newCollisions;
}
