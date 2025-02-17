#pragma once

#include "Vector2D.h"

class Actor;

struct HitResult {
    bool bHit = false;        
    Actor* hitActor = nullptr; 
    Vector2D hitLocation;
};
