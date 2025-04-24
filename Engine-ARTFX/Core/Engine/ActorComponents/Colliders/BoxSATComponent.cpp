#include "BoxSATComponent.h"
#include "Matrix4DRow.h"

BoxSATComponent::BoxSATComponent(Actor* owner, int updateOrder, Vector3D size, Vector3D relativePosition)
    :ColliderComponent(owner, updateOrder)
{
    SetRelativePosition(relativePosition);
    mSize = size;
}

bool BoxSATComponent::CheckCollisionWith(ColliderComponent* other)
{
    if (other->GetColliderType() == ColliderType::BoxSAT) {
        return CheckCollisionWithBoxSAT(static_cast<BoxSATComponent*>(other));
    }
    return false;
}

AABB BoxSATComponent::GetAABB()
{
    return mCachedAABB;
}

void BoxSATComponent::Update()
{
    std::vector<Vector3D> vertices = GetVertices();
    Vector3D min = vertices[0];
    Vector3D max = vertices[0];

    for (const auto& v : vertices) {
        min = Vector3D::Min(min, v);
        max = Vector3D::Max(max, v);
    }
    mCachedAABB = AABB(min, max);
}

std::vector<Vector3D> BoxSATComponent::GetAxes()
{
    Matrix4DRow transform = GetWorldTransform();
    return {
        Vector3D::Normalize(transform.GetXAxis()),
        Vector3D::Normalize(transform.GetZAxis()),
        Vector3D::Normalize(transform.GetYAxis()),
    };
}

std::vector<Vector3D> BoxSATComponent::GetVertices()
{
    std::vector<Vector3D> vertices;
    Vector3D halfSize = GetScaledSize() * 0.5f;
    Matrix4DRow transform = mOwner->GetTransformComponent().GetWorldTransform();

    // Génération des 8 sommets avec la transformation complète
    for (float x : {-1.0f, 1.0f}) {
        for (float y : {-1.0f, 1.0f}) {
            for (float z : {-1.0f, 1.0f}) {
                Vector3D vertex = Vector3D(x, y, z) * halfSize;
                vertex = transform.TransformPoint(vertex);
                vertices.push_back(vertex);
            }
        }
    }
    return vertices;
}

bool BoxSATComponent::CheckCollisionWithBoxSAT(BoxSATComponent* other)
{
    // Récupère tous les axes à tester
    std::vector<Vector3D> axes = GetAxes();
    const auto otherAxes = other->GetAxes();
    axes.insert(axes.end(), otherAxes.begin(), otherAxes.end());

    // Test des axes de séparation
    for (const auto& axis : axes) {
        auto proj1 = CalculateProjection(axis);
        auto proj2 = other->CalculateProjection(axis);

        if (proj1.second < proj2.first || proj2.second < proj1.first) {
            return false;
        }
    }
    return true;
}

std::pair<float, float> BoxSATComponent::CalculateProjection(const Vector3D& axis)
{
    std::vector<Vector3D> vertices = GetVertices();
    float min = Vector3D::Dot(axis, vertices[0]);
    float max = min;

    for (const auto& v : vertices) {
        float proj = Vector3D::Dot(axis, v);
        min = std::min(min, proj);
        max = std::max(max, proj);
    }

    return { min, max };
}

Vector3D BoxSATComponent::GetScaledSize() {
    return mSize * GetWorldTransform().GetScale();
}