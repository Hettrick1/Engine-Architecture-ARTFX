#pragma once

#include "Vertex.h"

class ColliderComponent;

struct CollisionDetection
{
	static bool IsColliding(ColliderComponent* a, ColliderComponent* b, Vector3D& normal, float& penetrationDepth);
	static bool IsCollidingBoxBox(ColliderComponent* a, ColliderComponent* b, Vector3D& normal, float& penetrationDepth);
	static bool IsCollidingMeshMesh(ColliderComponent* a, ColliderComponent* b, Vector3D& normal, float& penetrationDepth);
};