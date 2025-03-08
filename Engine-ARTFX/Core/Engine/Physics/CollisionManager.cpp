#include "CollisionManager.h"
#include "Actor.h"
#include "ICollisionListener.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include <utility>
#include <algorithm>

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{

    for (auto& pair : mColliders) 
    {
        for (auto* collider : pair.second) 
        {
            if (collider != nullptr)
            {
                delete collider;
            }
            collider = nullptr;
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

void CollisionManager::RemoveCollider(Actor* pOwner, ColliderComponent* pCollider)
{
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

                        if (isNewCollision1 && isNewCollision2) {
                            CalculateNormal(collider1, collider2);
                        }

                        if (isNewCollision1 && collider1->GetIsTriggerable()) {
                            collider1->NotifyListenersStarted();
                        }
                        else if (collider1->GetIsTriggerable()) {
                            collider1->NotifyListenersStay();
                        }

                        if (isNewCollision2 && collider2->GetIsTriggerable()) {
                            collider2->NotifyListenersStarted();
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
                    }
                    if (otherCollider->GetIsTriggerable()) {
                        otherCollider->SetHitResult(false, nullptr, nullptr);
                        otherCollider->NotifyListenersEnded();
                    }
                }
            }
        }
    }
    mCurrentCollisions = newCollisions;
}

void CollisionManager::CalculateNormal(ColliderComponent* collider1, ColliderComponent* collider2)
{
    // Récupérer les positions centrales des acteurs
    Vector3D pos1 = collider1->GetOwner()->GetTransformComponent().GetPosition();
    Vector3D pos2 = collider2->GetOwner()->GetTransformComponent().GetPosition();

    // Supposons que GetSize() retourne la taille complète du collider
    Vector3D halfSize1 = collider1->GetSize() * 0.5f;
    Vector3D halfSize2 = collider2->GetSize() * 0.5f;

    // Calculer les coins min et max pour chaque AABB
    Vector3D min1 = pos1 - halfSize1;
    Vector3D max1 = pos1 + halfSize1;
    Vector3D min2 = pos2 - halfSize2;
    Vector3D max2 = pos2 + halfSize2;

    // Calculer les recouvrements (overlap) sur chaque axe
    float overlapX = std::min(max1.x, max2.x) - std::max(min1.x, min2.x);
    float overlapY = std::min(max1.y, max2.y) - std::max(min1.y, min2.y);
    float overlapZ = std::min(max1.z, max2.z) - std::max(min1.z, min2.z);

    // Vérifier si une collision s'est produite
    if (overlapX <= 0 || overlapY <= 0 || overlapZ <= 0)
    {
        // Pas de collision, retourner
        return;
    }

    // Déterminer l'axe avec le plus petit recouvrement
    Vector3D normal;

    float minOverlap = std::min({ overlapX, overlapY, overlapZ });
    float depth = minOverlap;
    // Déterminer la direction avec une tolérance pour les égalités
    if (minOverlap == overlapX) {
        const float epsilon = 0.001f;
        if (pos1.x < pos2.x - epsilon) {
            normal = Vector3D(1, 0, 0);
        }
        else if (pos1.x > pos2.x + epsilon) {
            normal = Vector3D(-1, 0, 0);
        }
        else {
            normal = (pos1.x < pos2.x) ? Vector3D(-1, 0, 0) : Vector3D(1, 0, 0);
        }
    }
    if (minOverlap == overlapY) {
        const float epsilon = 0.001f;
        if (pos1.y < pos2.y - epsilon) {
            normal = Vector3D(0, 1, 0);
        }
        else if (pos1.x > pos2.x + epsilon) {
            normal = Vector3D(0, -1, 0);
        }
        else {
            normal = (pos1.x < pos2.x) ? Vector3D(0, -1, 0) : Vector3D(0, 1, 0);
        }
    }
    if (minOverlap == overlapZ) {
        const float epsilon = 0.001f;
        if (pos1.z < pos2.z - epsilon) {
            normal = Vector3D(0, 0, 1);
        }
        else if (pos1.z > pos2.z + epsilon) {
            normal = Vector3D(0, 0, -1);
        }
        else {
            normal = (pos1.x < pos2.x) ? Vector3D(0, 0, -1) : Vector3D(0, 0, 1);
        }
    }
     
    collider1->SetHitResult(true, collider2->GetOwner(), collider2, normal, depth);
    collider2->SetHitResult(true, collider1->GetOwner(), collider1, normal, depth);
}
