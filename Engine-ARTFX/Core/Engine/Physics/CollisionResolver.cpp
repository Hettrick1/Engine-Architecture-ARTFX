#include "CollisionResolver.h"
#include "RigidbodyComponent.h"

CollisionResolver::~CollisionResolver()
{
	for (auto& pair : mRigidbodies)
	{
		RigidbodyComponent* rb = pair.second;
		if (rb != nullptr)
		{
			delete rb;
		}
		rb = nullptr;
	}
	mRigidbodies.clear();
	for (auto& pair : mQuerryCollisions)
	{
		CollisionInfos* ci = pair.second;
		if (ci != nullptr)
		{
			delete ci;
		}
		ci = nullptr;
	}
	mQuerryCollisions.clear();
	for (auto& pair : mPhysicCollisions)
	{
		CollisionInfos* ci = pair.second;
		if (ci != nullptr)
		{
			delete ci;
		}
		ci = nullptr;
	}
	mPhysicCollisions.clear();
}

void CollisionResolver::RegisterRigidBody(Actor* pOwner, RigidbodyComponent* pRigidbody)
{
	if (mRigidbodies.find(pOwner) == mRigidbodies.end())
	{
		mRigidbodies[pOwner] = pRigidbody;
	}
	else
	{
		Log::Error(LogType::System, "You already have a rigidbody attached to this actor !");
	}
}

void CollisionResolver::RemoveRigidBody(Actor* pOwner, RigidbodyComponent* pRigidbody)
{
	auto it = mRigidbodies.find(pOwner);
	if (it != mRigidbodies.end())
	{
		mRigidbodies.erase(it);
	}
}

void CollisionResolver::UpdateRigidbodies()
{
	if (mRigidbodies.empty())
	{
		return;
	}
	for (auto it = mRigidbodies.begin(); it != mRigidbodies.end(); it++)
	{
		RigidbodyComponent* rb = it->second;
		if (rb != nullptr)
		{
			rb->Update();
		}
	}
}

void CollisionResolver::AddCollisionToQueue(CollisionInfos* pCollisionInfo)
{
	std::pair<ColliderComponent*, ColliderComponent*> colliders = pCollisionInfo->colliderPair;
	std::pair<Actor*, Actor*> actors = pCollisionInfo->actorPair;
	if (colliders.first->GetIsTriggerable() || colliders.second->GetIsTriggerable())
	{
		mQuerryCollisions[colliders] = pCollisionInfo;
	}
	else {
		mPhysicCollisions[actors] = pCollisionInfo;
	}
}

void CollisionResolver::ResolveCollisions()
{
	if (!mPhysicCollisions.empty())
	{
		CalculatePhysicCollisions();
	}
	if (!mQuerryCollisions.empty())
	{
		CalculateQuerryCollisions();
	}
}

void CollisionResolver::CalculateQuerryCollisions()
{
	for (auto it = mQuerryCollisions.begin(); it != mQuerryCollisions.end(); it++)
	{
		CollisionInfos* collision = it->second;
		std::pair<ColliderComponent*, ColliderComponent*> colliders = collision->colliderPair;
		switch (collision->type)
		{
		case CollisionType::Enter:
		{
			colliders.first->NotifyListenersStarted();
			colliders.second->NotifyListenersStarted();
			break;
		}
		case CollisionType::Stay:
		{
			colliders.first->NotifyListenersStay();
			colliders.second->NotifyListenersStay();
			break;
		}
		case CollisionType::Exit:
		{
			colliders.first->NotifyListenersEnded();
			colliders.second->NotifyListenersEnded();
			break;
		}
		default:
		{
			Log::Error(LogType::Error, "The collision type is needed for querry collisions !");
			break;
		}
		}
	}
}

void CollisionResolver::CalculatePhysicCollisions()
{
	for (auto it = mPhysicCollisions.begin(); it != mPhysicCollisions.end(); it++)
	{
		CollisionInfos* collision = it->second;

		std::pair<Actor*, Actor*> actors = collision->actorPair;

		RigidbodyComponent* rbA = actors.first->GetRigidBody(); 
		RigidbodyComponent* rbB = actors.second->GetRigidBody();

		bool isStaticA = (rbA && rbA->IsStatic()) || (rbA && rbA->GetMass() > 10000);
		bool isStaticB = (rbB && rbB->IsStatic()) || (rbB && rbB->GetMass() > 10000);

		if (!rbA && !rbB)
		{
			continue;
		}

		switch (collision->type)
		{
			case CollisionType::Enter:
			{
				ColliderComponent* colliderA = collision->colliderPair.first;
				ColliderComponent* colliderB = collision->colliderPair.second;
				Vector3D normal = collision->normal;
				float penetrationDepth = collision->depth;

				if (!isStaticA && !isStaticB) {
					actors.first->GetTransformComponent().Translate((normal * -1) * (penetrationDepth * 0.5f));
					actors.second->GetTransformComponent().Translate(normal * (penetrationDepth * 0.5f));
				}
				else if (!isStaticA) {
					actors.first->GetTransformComponent().Translate((normal * -1) * penetrationDepth);
				}
				else if (!isStaticB) {
					actors.second->GetTransformComponent().Translate(normal * penetrationDepth);
				}

				Vector3D velocityA = (rbA && !isStaticA) ? rbA->GetVelocity() : Vector3D(0);
				Vector3D velocityB = (rbB && !isStaticB) ? rbB->GetVelocity() : Vector3D(0);

				Vector3D relativeVelocity = velocityA - velocityB;
				float vRel = Vector3D::Dot(relativeVelocity, normal);

				/*if (vRel >= 0)
					continue;*/

				float e = (rbA ? rbA->GetBounciness() : 0.0f) * (rbB ? rbB->GetBounciness() : 0.0f);
				float invMassA = (rbA && rbA->GetMass() > 0.0f) ? 1.0f / rbA->GetMass() : 0.0f;
				float invMassB = (rbB && rbB->GetMass() > 0.0f) ? 1.0f / rbB->GetMass() : 0.0f;

				float j = -(1 + e) * vRel / (invMassA + invMassB);
				Vector3D impulse = j * normal;

				if (rbA && !isStaticA) rbA->ResolveCollision(impulse * invMassA);
				if (rbB && !isStaticB) rbB->ResolveCollision((impulse * -1) * invMassB);

				break;
			}
			case CollisionType::Stay:
			{
				break;
			}
			case CollisionType::Exit:
			{
				break;
			}
			default:
			{
				Log::Error(LogType::Error, "The collision type is needed for physic collisions !");
				break;
			}
		}
	}
}

