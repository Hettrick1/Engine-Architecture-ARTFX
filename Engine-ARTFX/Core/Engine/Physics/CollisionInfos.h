#pragma once

#include <utility>
#include "Actor.h"
#include "ColliderComponent.h"

struct CollisionInfos
{
	std::pair<Actor*, Actor*> actorPair;
	std::pair<ColliderComponent*, ColliderComponent*> colliderPair;
};