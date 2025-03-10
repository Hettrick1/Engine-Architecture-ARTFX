#pragma once

#include "CollisionInfos.h"
#include "ColliderComponent.h"
#include "Actor.h"

#include <unordered_map>
#include <utility>
#include <algorithm>

class RigidbodyComponent;

namespace CollisionUtils {
	struct CollisionPairHash {
		std::size_t operator()(const std::pair<ColliderComponent*, ColliderComponent*>& pair) const {
			ColliderComponent* first = std::min(pair.first, pair.second);
			ColliderComponent* second = std::max(pair.first, pair.second);
			auto h1 = std::hash<ColliderComponent*>{}(first);
			auto h2 = std::hash<ColliderComponent*>{}(second);
			return h1 ^ (h2 << 1);
		}
	};
	struct ActorPairHash {
		std::size_t operator()(const std::pair<Actor*, Actor*>& pair) const {
			Actor* first = std::min(pair.first, pair.second);
			Actor* second = std::max(pair.first, pair.second);
			auto h1 = std::hash<Actor*>{}(first);
			auto h2 = std::hash<Actor*>{}(second);
			return h1 ^ (h2 << 1);
		}
	};
	struct CollisionPairEqual {
		bool operator()(const std::pair<ColliderComponent*, ColliderComponent*>& lhs,
			const std::pair<ColliderComponent*, ColliderComponent*>& rhs) const {
			return (lhs.first == rhs.first && lhs.second == rhs.second) ||
				(lhs.first == rhs.second && lhs.second == rhs.first);
		}
	};

	struct ActorPairEqual {
		bool operator()(const std::pair<Actor*, Actor*>& lhs,
			const std::pair<Actor*, Actor*>& rhs) const {
			return (lhs.first == rhs.first && lhs.second == rhs.second) ||
				(lhs.first == rhs.second && lhs.second == rhs.first);
		}
	};
}

class CollisionResolver
{
public:
	CollisionResolver() = default;
	~CollisionResolver();
	CollisionResolver(const CollisionResolver&) = delete;
	CollisionResolver& operator=(const CollisionResolver&) = delete;

	void UpdateRigidbodies();
	void ResolveCollisions();
	void CalculateQuerryCollisions();
	void CalculatePhysicCollisions();

	void ApplyReactionForce();

	void RegisterRigidBody(Actor* pOwner, RigidbodyComponent* pRigidbody);
	void RemoveRigidBody(Actor* pOwner, RigidbodyComponent* pRigidbody);
	void AddCollisionToQueue(CollisionInfos* pCollisionInfo);
private:
	std::unordered_map<std::pair<Actor*, Actor*>, CollisionInfos*,
		CollisionUtils::ActorPairHash, CollisionUtils::ActorPairEqual> mPhysicCollisions;
	std::unordered_map<std::pair<ColliderComponent*, ColliderComponent*>, CollisionInfos*,
		CollisionUtils::CollisionPairHash, CollisionUtils::CollisionPairEqual> mQuerryCollisions;
	std::unordered_map<Actor*, RigidbodyComponent*> mRigidbodies;
	std::unordered_map<RigidbodyComponent*, Vector3D> mReactionForce;
};
