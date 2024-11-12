#pragma once

#include <SDL_rect.h>
#include "Vector2D.h"

struct Rectangle
{
    Vector2D position;
    Vector2D dimensions;

    SDL_Rect ToSdlRect() const
    {
        return SDL_Rect{
            static_cast<int>(position.x),
            static_cast<int>(position.y),
            static_cast<int>(dimensions.x),
            static_cast<int>(dimensions.y) };
    }
};
