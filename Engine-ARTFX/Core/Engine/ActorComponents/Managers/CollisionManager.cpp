#include "CollisionManager.h"
#include "Actor.h"
#include "ICollisionListener.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include <utility>
#include <algorithm>

CollisionManager& CollisionManager::Instance()
{
    static CollisionManager instance;
    return instance;
}

CollisionManager::~CollisionManager()
{

    for (auto& pair : mColliders) 
    {
        for (auto* collider : pair.second) 
        {
            delete collider;
        }
    }
    mColliders.clear();
    mCurrentCollisions.clear();
}

void CollisionManager::RegisterCollider(Actor* pOwner, ColliderComponent* pCollider)
{
    if (pOwner && pCollider) {
        mColliders[pOwner].push_back(pCollider);
    }
}

void CollisionManager::RegisterRigidbody(Actor* pOwner, RigidbodyComponent* pRigidbody)
{
    if (mRigidbodies.find(pOwner) == mRigidbodies.end()) {
        mRigidbodies[pOwner] = pRigidbody;
    }
}

void CollisionManager::CheckCollisions()
{
    if (mColliders.empty()) {
        return;
    }

    std::unordered_map<ColliderComponent*, std::unordered_set<ColliderComponent*>> newCollisions;

    // Get active actor
    std::vector<Actor*> activeActors;
    for (auto& pair : mColliders) {
        if (pair.first->GetState() == ActorState::Active) {
            activeActors.push_back(pair.first);
        }
    }

    // Begin and stay collision handling
    for (size_t i = 0; i < activeActors.size(); ++i) {
        for (size_t j = i + 1; j < activeActors.size(); ++j) {
            Actor* actor1 = activeActors[i];
            Actor* actor2 = activeActors[j];

            auto& colliders1 = mColliders[actor1];
            auto& colliders2 = mColliders[actor2];

            for (auto* collider1 : colliders1) {
                for (auto* collider2 : colliders2) {
                    if (collider1->CheckCollisionWith(collider2)) {
                        bool isNewCollision1 = mCurrentCollisions[collider1].find(collider2) == mCurrentCollisions[collider1].end();
                        bool isNewCollision2 = mCurrentCollisions[collider2].find(collider1) == mCurrentCollisions[collider2].end();

                        collider1->SetHitResult(true, collider2->GetOwner(), collider2); 
                        collider2->SetHitResult(true, collider1->GetOwner(), collider2);

                        if (isNewCollision1 && collider1->GetIsTriggerable()) {
                            collider1->NotifyListenersStarted();
                            // Call Rigidbody event if it exists
                            Actor* actor1 = collider1->GetOwner(); 
                            if (auto* rb1 = mRigidbodies[actor1]) { 
                                rb1->OnCollisionEnter(collider2); 
                            }
                        }
                        else if (collider1->GetIsTriggerable()) {
                            collider1->NotifyListenersStay();
                        }

                        if (isNewCollision2 && collider2->GetIsTriggerable()) {
                            collider2->NotifyListenersStarted();

                            // Call Rigidbody event if it exists
                            Actor* actor2 = collider2->GetOwner();
                            if (auto* rb2 = mRigidbodies[actor2]) {
                                rb2->OnCollisionEnter(collider1);
                            }
                        }
                        else if (collider2->GetIsTriggerable()) {
                            collider2->NotifyListenersStay();
                        }

                        newCollisions[collider1].insert(collider2);
                        newCollisions[collider2].insert(collider1);
                    }
                }
            }
        }
    }
    // End of collision handling
    std::unordered_set<std::pair<ColliderComponent*, ColliderComponent*>, CollisionPairHash> processedCollisions;
    for (auto& pair : mCurrentCollisions) {
        ColliderComponent* collider = pair.first;
        for (auto* otherCollider : pair.second) {
            if (newCollisions[collider].find(otherCollider) == newCollisions[collider].end()) {
                auto collisionPair = std::minmax(collider, otherCollider);
                if (processedCollisions.find(collisionPair) == processedCollisions.end()) {
                    processedCollisions.insert(collisionPair);

                    if (collider->GetIsTriggerable()) {
                        collider->SetHitResult(false, nullptr, nullptr);
                        collider->NotifyListenersEnded();

                        Actor* actor1 = collider->GetOwner(); 
                        if (auto* rb1 = mRigidbodies[actor1]) { 
                            rb1->OnCollisionExit(otherCollider); 
                        }
                    }
                    if (otherCollider->GetIsTriggerable()) {
                        otherCollider->SetHitResult(false, nullptr, nullptr);
                        otherCollider->NotifyListenersEnded();

                        Actor* actor2 = otherCollider->GetOwner();
                        if (auto* rb2 = mRigidbodies[actor2]) {
                            rb2->OnCollisionExit(collider);
                        } 
                    }
                }
            }
        }
    }

    mCurrentCollisions = newCollisions;
}
