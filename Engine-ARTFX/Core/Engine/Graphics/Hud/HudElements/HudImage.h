#pragma once
#include "HudElement.h"
#include "RendererOpenGl.h"
#include "Texture.h"

class HudImage :
    public HudElement
{
public:
    HudImage(Texture& pTexture, Vector2D pPosition, Vector2D pSize = 1, Vector2D pOrigin = 0);
        
    void Draw(RendererOpenGl& renderer) override;

    void SetTexture(Texture& pTexture);

private:
    Texture mTexture;
    float mWidth, mHeight;
    Vector2D mOrigin;
};

