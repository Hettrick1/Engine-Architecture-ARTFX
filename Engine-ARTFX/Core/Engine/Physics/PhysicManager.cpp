#include "PhysicManager.h"

#include "CollisionManager.h"
#include "CollisionResolver.h"
#include "Actor.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"

PhysicManager& PhysicManager::Instance()
{
    static PhysicManager instance;
    return instance;
}

PhysicManager::PhysicManager()
{
    mCollisionResolver = new CollisionResolver();
    mCollisionManager = new CollisionManager();
}


PhysicManager::~PhysicManager()
{
    if (mCollisionManager != nullptr)
    {
        delete mCollisionManager;
        mCollisionManager = nullptr;
    }
    if (mCollisionResolver != nullptr)
    {
        delete mCollisionResolver;
        mCollisionResolver = nullptr;
    }
}

void PhysicManager::Update()
{
    std::unordered_map<Actor*, Vector3D> previousPositions;
    for (auto& pair : mCollisionResolver->GetRigidbodies()) {
        previousPositions[pair.first] = pair.first->GetTransformComponent().GetPosition();
    }

    mCollisionResolver->UpdateRigidbodies();
    mCollisionManager->UpdateColliders();
    mCollisionManager->CheckCollisions();
    mCollisionResolver->ResolveCollisions();

    for (auto& pair : previousPositions) {
        Actor* actor = pair.first;
        Vector3D oldPos = pair.second;
        Vector3D newPos = actor->GetTransformComponent().GetPosition();

        float maxAllowedMovement = 10.0f;
        if (Vector3D::Distance(oldPos, newPos) > maxAllowedMovement) {
            Vector3D direction = Vector3D::Normalize(newPos - oldPos);
            Vector3D limitedPos = oldPos + direction * maxAllowedMovement;
            actor->SetPosition(limitedPos);

            RigidbodyComponent* rb = actor->GetRigidBody();
            if (rb) {
                rb->SetVelocity(Vector3D(0));
            }
        }
    }
}

void PhysicManager::RegisterCollider(Actor* pOwner, ColliderComponent* pCollider)
{
    mCollisionManager->RegisterCollider(pOwner, pCollider);
}

void PhysicManager::RemoveCollider(Actor* pOwner, ColliderComponent* pCollider)
{
    mCollisionManager->RemoveCollider(pOwner, pCollider);
}

void PhysicManager::RegisterRigidBody(Actor* pOwner, RigidbodyComponent* pRigidbody)
{
    mCollisionResolver->RegisterRigidBody(pOwner, pRigidbody);
}

void PhysicManager::RemoveRigidBody(Actor* pOwner, RigidbodyComponent* pRigidbody)
{
    mCollisionResolver->RemoveRigidBody(pOwner, pRigidbody);
}

void PhysicManager::AddCollisionToQueue(CollisionInfos* pCollisionInfo)
{
    mCollisionResolver->AddCollisionToQueue(pCollisionInfo);
}
