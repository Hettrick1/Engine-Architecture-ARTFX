#include "HudImage.h"

HudImage::HudImage(Texture& pTexture, Vector2D pPosition, Vector2D pSize, Vector2D pOrigin)
    : mTexture(pTexture), mWidth(pTexture.GetTextureSize().x * pSize.x), mHeight(pTexture.GetTextureSize().y * pSize.y), mOrigin(pOrigin)
{
    SetPosition(pPosition.x, pPosition.y);
}

void HudImage::Draw(RendererOpenGl& renderer)
{
    Rectangle rect;
    rect.dimensions = { mWidth, mHeight };
    rect.position = { mPositionX, mPositionY };

    renderer.DrawHudImage(mTexture, rect, mOrigin);
}