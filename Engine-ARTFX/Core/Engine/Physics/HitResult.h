#pragma once

#include "Vector3D.h"

class Actor;
class ColliderComponent;

struct HitResult {
    bool Hit;          
    Vector3D HitPoint;  
    Vector3D Normal;
    Actor* HitActor;
    ColliderComponent* HitCollider;
    float Distance;
};
