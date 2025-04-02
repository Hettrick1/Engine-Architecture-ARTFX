#pragma once

#include "Vector3D.h"

class Actor;
class ColliderComponent;

struct HitResult {
    bool Hit = 0;          
    Vector3D HitPoint = Vector3D::zero;  
    Vector3D Normal = Vector3D::zero;
    Actor* HitActor = nullptr;
    ColliderComponent* HitCollider = nullptr;
    float Distance = 0;
};
