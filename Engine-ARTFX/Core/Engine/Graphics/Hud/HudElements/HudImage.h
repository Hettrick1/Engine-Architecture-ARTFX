#pragma once
#include "HudElement.h"
#include "RendererOpenGl.h"
#include "Texture.h"

class HudImage :
    public HudElement
{
public:
    HudImage(Texture& pTexture, Vector2D pPosition, Vector2D pOrigin = Vector2D(0.5, 0.5));
        
    void Draw(RendererOpenGl& renderer) override;

private:
    Texture mTexture;
    float mWidth, mHeight;
    Vector2D mOrigin;
};

