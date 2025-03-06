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

void CollisionManager::RegisterCollider(Actor* pOwner, ColliderComponent* pCollider)
{
    mAllColliders.push_back(pCollider);
}

void CollisionManager::CheckCollisions()
{
    if (mAllColliders.size() <= 0)
    {
        return;
    }
    // check only if the actor is active
    std::vector<ColliderComponent*> activeColliders;
    for (auto& collider : mAllColliders) {
        if (collider->GetOwner()->GetState() == ActorState::Active) {
            activeColliders.push_back(collider);
        }
    }
    std::unordered_map<ColliderComponent*, std::unordered_set<ColliderComponent*>> newCollisions;
    // for each collisions check their state
    for (size_t i = 0; i < activeColliders.size() - 1; ++i) {
        for (size_t j = i + 1; j < activeColliders.size(); ++j) {
            auto* collider1 = activeColliders[i];
            auto* collider2 = activeColliders[j];

            // check collision
            if (collider1->CheckCollisionWith(collider2)) {
                // check if the collision is new to call anly one time the on trigger enter function
                bool isNewCollision1 = mCurrentCollisions[collider1].find(collider2) == mCurrentCollisions[collider1].end();
                bool isNewCollision2 = mCurrentCollisions[collider2].find(collider1) == mCurrentCollisions[collider2].end();

                if (isNewCollision1) {
                    if (collider1->GetIsTriggerable()) {
                        // set the hit result of the collision
                        collider1->SetHitResult(true, collider2->GetOwner());
                        collider1->NotifyListenersStarted();
                    }
                }
                // if not new call on trigger stay
                else {
                    if (collider1->GetIsTriggerable()) {
                        collider1->NotifyListenersStay();
                    }
                }

                if (isNewCollision2) {
                    if (collider2->GetIsTriggerable()) {
                        // set the hit result of the collision
                        collider2->SetHitResult(true, collider1->GetOwner());
                        collider2->NotifyListenersStarted();
                    }
                }
                // if not new call on trigger stay
                else {
                    if (collider2->GetIsTriggerable()) {
                        collider2->NotifyListenersStay();
                    }
                }

                // add the colliders to the new collision
                newCollisions[collider1].insert(collider2);
                newCollisions[collider2].insert(collider1);
            }
        }
    }

    // if no collisions were detected
    // check if the previous trigger collisions are ended
    std::unordered_set<std::pair<ColliderComponent*, ColliderComponent*>, CollisionPairHash> processedCollisions;

    for (auto& pair : mCurrentCollisions) { 
        ColliderComponent* collider = pair.first; 
        std::unordered_set<ColliderComponent*>& previousCollisions = pair.second; 
        for (auto* otherCollider : previousCollisions) 
        { 
            // if not in new collisions the collision was ended last frame
            if (newCollisions[collider].find(otherCollider) == newCollisions[collider].end()) 
            { 
                std::pair<ColliderComponent*, ColliderComponent*> collisionPair = std::minmax(collider, otherCollider); 

                // check to call only one time the on trigger exit function
                if (processedCollisions.find(collisionPair) == processedCollisions.end()) 
                { 
                    processedCollisions.insert(collisionPair);
                    if (collider->GetIsTriggerable()) 
                    { 
                        collider->SetHitResult(true, otherCollider->GetOwner());
                        collider->NotifyListenersEnded(); 
                    }
                    if (otherCollider->GetIsTriggerable()) 
                    {
                        otherCollider->SetHitResult(true, collider->GetOwner());
                        otherCollider->NotifyListenersEnded(); 
                    }
                    // reset hit result
                    collider->SetHitResult(false, nullptr); 
                    otherCollider->SetHitResult(false, nullptr); 
                }
            }
        }
    }
    mCurrentCollisions = newCollisions;
}
