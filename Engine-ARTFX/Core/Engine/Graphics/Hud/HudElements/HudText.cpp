#include "HudText.h"

HudText::HudText(const std::string& text, float x, float y, float scale, Vector3D color, TextAlignment alignment)
    : mText(text), mScale(scale), mColor(color), mAlignment(alignment)
{
    SetPosition(x, y);
}

void HudText::Draw(RendererOpenGl& renderer)
{
    TextRenderer::Instance().RenderText(mText, mPositionX, mPositionY, mScale, mColor, mAlignment);
}

void HudText::SetText(std::string pText)
{
    mText = pText;
}
