#pragma once

#include "Vector3D.h"

class Actor;

struct HitResult {
    bool bHit = false;        
    Actor* hitActor = nullptr; 
    Vector3D hitLocation;
};
