#include "BoxSATComponent.h"
#include "Matrix4DRow.h"
#include "IRenderer.h"

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
    AABB aabb = AABB(GetWorldPosition() - mSize, GetWorldPosition() + mSize);
    mCachedAABB = aabb;
}

std::vector<Vector3D> BoxSATComponent::GetVertices()
{
    std::vector<Vector3D> vertices;
    Vector3D halfSize = GetScaledSize();
    Matrix4DRow transform = GetWorldTransform();

    // Génération des 8 sommets avec la transformation complète
    for (float x : {-1.0f, 1.0f}) {
        for (float y : {-1.0f, 1.0f}) {
            for (float z : {-1.0f, 1.0f}) {
                Vector3D vertex = Vector3D(x, y, z) * halfSize;
                vertex = transform.TransformVector(vertex);
                vertices.push_back(vertex);
            }
        }
    }
    return vertices;
}

void BoxSATComponent::DebugDraw(IRenderer& renderer)
{
    if (mOwner->GetState() == ActorState::Active)
    {
        AABB aabb = AABB(GetWorldPosition() - mSize, GetWorldPosition() + mSize);

        Matrix4DRow wt;

        wt = Matrix4DRow::CreateScale(mSize * 2);
        wt *= Matrix4DRow::CreateTranslation(GetWorldPosition() - mSize);

        renderer.DrawDebugBox(aabb.min, aabb.max, wt);
    }
}

bool BoxSATComponent::CheckCollisionWithBoxSAT(BoxSATComponent* other)
{
    Vector3D axesA[3], axesB[3];
    GetAxes(axesA);
    other->GetAxes(axesB);

    Vector3D centerA = GetWorldPosition();
    Vector3D centerB = other->GetWorldPosition();
    Vector3D t = centerB - centerA;

    // Test des 15 axes (3 de A, 3 de B, 9 croisés)
    for (int i = 0; i < 3; i++) {
        if (!OverlapOnAxis(other, axesA[i])) return false;
    }
    for (int i = 0; i < 3; i++) {
        if (!OverlapOnAxis(other, axesB[i])) return false;
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            Vector3D axis = Vector3D::Cross(axesA[i], axesB[j]);
            if (axis.LengthSq() > 0.001f && !OverlapOnAxis(other, Vector3D::Normalize(axis))) {
                return false;
            }
        }
    }
    return true;
}

bool BoxSATComponent::OverlapOnAxis(BoxSATComponent* other, const Vector3D& axis) {
    auto projA = CalculateProjection(axis);
    auto projB = other->CalculateProjection(axis);
    return projA.second >= projB.first && projB.second >= projA.first;
}

void BoxSATComponent::GetAxes(Vector3D axes[3])
{
    Matrix4DRow transform = GetWorldTransform();
    axes[0] = Vector3D::Normalize(transform.GetXAxis()); // Right
    axes[1] = Vector3D::Normalize(transform.GetYAxis()); // Forward
    axes[2] = Vector3D::Normalize(transform.GetZAxis()); // Up
}

std::pair<float, float> BoxSATComponent::CalculateProjection(const Vector3D& axis)
{
    Vector3D axes[3];
    GetAxes(axes);
    Vector3D scaledExtents = GetScaledSize();

    float proj = Vector3D::Dot(GetWorldPosition(), axis);
    float radius =
        scaledExtents.x * std::abs(Vector3D::Dot(axes[0], axis)) +
        scaledExtents.y * std::abs(Vector3D::Dot(axes[1], axis)) +
        scaledExtents.z * std::abs(Vector3D::Dot(axes[2], axis));

    return { proj - radius, proj + radius };
}

Vector3D BoxSATComponent::GetScaledSize() {
    Vector3D scale = mOwner->GetTransformComponent().GetSize();
    return Vector3D(
        mSize.x * std::abs(scale.x),
        mSize.y * std::abs(scale.y),
        mSize.z * std::abs(scale.z)
    );
}