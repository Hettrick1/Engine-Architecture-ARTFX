#pragma once
#include "HudElement.h"
#include "RendererOpenGl.h"
class HudImage :
    public HudElement
{
public:
    HudImage(unsigned int textureID, float x, float y, float width, float height)
        : mTextureID(textureID), mWidth(width), mHeight(height) {
        SetPosition(x, y);
    }

    void Draw(RendererOpenGl& renderer) override {
        //renderer.DrawImage(mTextureID, mPositionX, mPositionY, mWidth, mHeight);
    }

private:
    unsigned int mTextureID;
    float mWidth, mHeight;
};

