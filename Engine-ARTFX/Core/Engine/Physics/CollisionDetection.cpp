#include "CollisionDetection.h"
#include "ColliderComponent.h"

bool CollisionDetection::IsColliding(ColliderComponent* a, ColliderComponent* b, Vector3D& normal, float& penetrationDepth)
{
	ColliderType aType = a->GetColliderType();
	ColliderType bType = b->GetColliderType();

	if (aType == ColliderType::Box && bType == ColliderType::Box)
	{
        return IsCollidingBoxBox(a, b, normal, penetrationDepth);
	}
	if (aType == ColliderType::Mesh && bType == ColliderType::Mesh)
	{
		return IsCollidingMeshMesh(a, b, normal, penetrationDepth);
	}
	return false;
}

bool CollisionDetection::IsCollidingBoxBox(ColliderComponent* a, ColliderComponent* b, Vector3D& normal, float& penetrationDepth)
{
    std::vector<Vector3D> verticesA = a->GetWorldVertices();
    std::vector<Vector3D> verticesB = b->GetWorldVertices();

    std::vector<Vector3D> axes = {
        a->GetWorldTransform().GetXAxis(), a->GetWorldTransform().GetZAxis(), a->GetWorldTransform().GetYAxis(),
        b->GetWorldTransform().GetXAxis(), b->GetWorldTransform().GetZAxis(), b->GetWorldTransform().GetYAxis()
    };

    /*std::vector<Vector3D> axes = {
        a->RelativeRight(), a->RelativeUp(), a->RelativeForward(),
        b->RelativeRight(), b->RelativeUp(), b->RelativeForward()
    };*/

    float minPenetration = FLT_MAX;
    Vector3D minAxis;

    for (const Vector3D& axis : axes)
    {
        float minA = FLT_MAX, maxA = -FLT_MAX;
        float minB = FLT_MAX, maxB = -FLT_MAX;

        for (const Vector3D& vertex : verticesA)
        {
            float projection = Vector3D::Dot(vertex, axis);
            minA = std::min(minA, projection);
            maxA = std::max(maxA, projection);
        }

        for (const Vector3D& vertex : verticesB)
        {
            float projection = Vector3D::Dot(vertex, axis);
            minB = std::min(minB, projection);
            maxB = std::max(maxB, projection);
        }

        if (maxA < minB || maxB < minA)
        {
            return false;
        }

        float penetration = std::min(maxA, maxB) - std::max(minA, minB);
        if (penetration < minPenetration)
        {
            minPenetration = penetration;
            minAxis = axis;
        }
    }

    normal = minAxis;
    penetrationDepth = minPenetration;
    return true;
}

bool CollisionDetection::IsCollidingMeshMesh(ColliderComponent* a, ColliderComponent* b, Vector3D& normal, float& penetrationDepth)
{
    return false;
}
