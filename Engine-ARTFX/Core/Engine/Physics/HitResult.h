#pragma once

#include "Vector3D.h"

class Actor;

struct HitResult {
    bool bHit = false;        
    Actor* hitActor = nullptr; 
    Vector3D hitLocation;
    Vector3D A;
    Vector3D B;
    Vector3D Normal;
    float Depth;
};
