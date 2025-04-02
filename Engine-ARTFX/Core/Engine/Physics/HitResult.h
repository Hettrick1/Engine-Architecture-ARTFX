#pragma once

#include "Vector3D.h"

struct HitResult {
    bool Hit;          
    Vector3D HitPoint;  
    Vector3D Normal;    
    float Distance;
};
