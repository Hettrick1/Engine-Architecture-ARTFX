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
		if (mQuerryCollisions.find(colliders) == mQuerryCollisions.end())
		{
			mQuerryCollisions[colliders] = pCollisionInfo;
		}
	}
	else {
		if (mPhysicCollisions.find(actors) == mPhysicCollisions.end())
		{
			mPhysicCollisions[actors] = pCollisionInfo;
		}
	}
}

void CollisionResolver::ResolveCollisions()
{
	Log::Info("" + std::to_string(mPhysicCollisions.size()));
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

		Vector3D vA = collision->velocityPair.first;
		Vector3D vB = collision->velocityPair.second;

		bool isStaticA = (rbA && rbA->IsStatic()) || (rbA && rbA->GetMass() > 10000);
		bool isStaticB = (rbB && rbB->IsStatic()) || (rbB && rbB->GetMass() > 10000);

		bool isGroundedA = ((rbA && rbA->IsStatic()) || (rbA && rbA->GetMass() > 10000) || (rbA && rbA->GetIsGrounded()));
		bool isGroundedB = ((rbB && rbB->IsStatic()) || (rbB && rbB->GetMass() > 10000) || (rbB && rbB->GetIsGrounded()));

		Vector3D colPos1 = collision->positionPair.first;
		Vector3D colPos2 = collision->positionPair.second;

		Vector3D normal = Vector3D(0,1,0);//collision->normal;
		normal = Vector3D::Normalize(normal);

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
				float penetrationDepth = collision->depth;

				if (!isStaticA && !isStaticB) {
					if (mCollisionPosition.find(actors.first) == mCollisionPosition.end())
					{
						mCollisionPosition[actors.first] = colPos1;
					}
					if (mCollisionPosition.find(actors.second) == mCollisionPosition.end())
					{
						mCollisionPosition[actors.second] = colPos2;
					}
				}
				else if (!isStaticA) {
					if (mCollisionPosition.find(actors.first) == mCollisionPosition.end())
					{
						mCollisionPosition[actors.first] = colPos1;
					}
				} 
				else if (!isStaticB) {
					if (mCollisionPosition.find(actors.second) == mCollisionPosition.end())
					{
						mCollisionPosition[actors.second] = colPos2;
					}
				}

				if (isGroundedA && normal.z > 0.1)
				{
					rbB->SetIsGrounded(true);
				}
				if (isGroundedB && normal.z > 0.1)
				{
					rbA->SetIsGrounded(true);
				}

				Vector3D velocityA = (rbA && !isStaticA) ? vA : Vector3D(0);
				Vector3D velocityB = (rbB && !isStaticB) ? vB : Vector3D(0);

				Vector3D relativeVelocity = velocityA - velocityB;
				float vRel = Vector3D::Dot(relativeVelocity, normal);

				float e = (rbA ? rbA->GetBounciness() : 0.0f) * (rbB ? rbB->GetBounciness() : 0.0f);
				float invMassA = (rbA && rbA->GetMass() > 0.0f) ? 1.0f / rbA->GetMass() : 0.0f;
				float invMassB = (rbB && rbB->GetMass() > 0.0f) ? 1.0f / rbB->GetMass() : 0.0f;

				float j = -(1 + e) * vRel / (invMassA + invMassB);
				Vector3D impulse = j * normal;

				if (rbA && !isStaticA)
				{
					if (mReactionForce.find(rbA) == mReactionForce.end())
					{
						mReactionForce[rbA] = impulse * invMassA;
					}
				}
				if (rbB && !isStaticB)
				{
					if (mReactionForce.find(rbB) == mReactionForce.end())
					{
						mReactionForce[rbB] = (impulse*-1) * invMassA;
					}
				}
				break;
			}
			case CollisionType::Stay:
			{
				break;
			}
			case CollisionType::Exit:
			{
				if (isGroundedA && normal.z > 0.1)
				{
					rbB->SetIsGrounded(false);
				}
				if (isGroundedB && normal.z > 0.1)
				{
					rbA->SetIsGrounded(false);
				}
				break;
			}
			default:
			{
				Log::Error(LogType::Error, "The collision type is needed for physic collisions !");
				break;
			}
		}
	}
	mPhysicCollisions.clear();
	ApplyReactionForce();
}

void CollisionResolver::ApplyReactionForce()
{
	for (auto it = mCollisionPosition.begin(); it != mCollisionPosition.end(); it++)
	{
		it->first->SetPosition(it->second);
	}
	mCollisionPosition.clear();
	for (auto it = mReactionForce.begin(); it != mReactionForce.end(); it++)
	{
		it->first->ResolveCollision(it->second);
	}
	mReactionForce.clear();
}

