#pragma once

#include <utility>
#include "Actor.h"
#include "ColliderComponent.h"

enum class CollisionType
{
	Enter,
	Stay,
	Exit
};

struct CollisionInfos
{
	CollisionInfos(
		std::pair<Actor*, Actor*> pActorPair, 
		std::pair<ColliderComponent*, ColliderComponent*> pColliderPair,
		CollisionType pType,
		Vector3D pNormal,
		float pDepth
	)
	{
		actorPair = pActorPair;
		colliderPair = pColliderPair;
		type = pType;
		normal = pNormal;
		depth = pDepth;
	}
	std::pair<Actor*, Actor*> actorPair;
	std::pair<ColliderComponent*, ColliderComponent*> colliderPair;
	CollisionType type;
	Vector3D normal;
	float depth;
};