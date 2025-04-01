#include "HudText.h"

HudText::HudText(const std::string& text, float x, float y, float scale, Vector3D color)
    : mText(text), mScale(scale), mColor(color) 
{
    SetPosition(x, y);
}

void HudText::Draw(RendererOpenGl& renderer)
{
    TextRenderer::Instance().RenderText(mText, mPositionX, mPositionY, mScale, mColor);
}
