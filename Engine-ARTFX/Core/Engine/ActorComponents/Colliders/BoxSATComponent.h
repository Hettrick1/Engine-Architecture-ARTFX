#pragma once
#include "ColliderComponent.h"
#include "Physics/AABB.h"
#include "Quaternion.h"

class BoxSATComponent : public ColliderComponent {
public :
    BoxSATComponent() = delete;
    BoxSATComponent(Actor* owner, int updateOrder, Vector3D size = 1, Vector3D relativePosition = Vector3D::zero);

    ColliderType GetColliderType() const override { return ColliderType::BoxSAT; }
    bool CheckCollisionWith(ColliderComponent* other) override;
    AABB GetAABB() override;
    void Update() override;

    std::vector<Vector3D> GetAxes();
    std::vector<Vector3D> GetVertices();


private : 
    bool CheckCollisionWithBoxSAT(BoxSATComponent* other);
    std::pair<float, float> CalculateProjection(const Vector3D& axis);
    Vector3D GetScaledSize();
private :
    AABB mCachedAABB;
};