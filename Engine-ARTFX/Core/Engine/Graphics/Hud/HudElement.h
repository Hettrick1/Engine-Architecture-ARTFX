#pragma once

#include "Vector2D.h"
#include "RendererOpenGl.h"

class HudElement
{
public:
    virtual ~HudElement() = default;
    virtual void Draw(RendererOpenGl& renderer) = 0;

    void SetPosition(float x, float y);
    inline Vector2D GetPosition() const { return { mPositionX, mPositionY }; }

protected:
    float mPositionX, mPositionY;
};

