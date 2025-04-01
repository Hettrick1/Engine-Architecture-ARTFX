#pragma once
#include "HudElement.h"
#include "TextRenderer.h"
#include "RendererOpenGl.h"
#include "TextAlignementEnum.h"

class HudText :
    public HudElement
{
public:
    HudText(const std::string& text, float x, float y, float scale, Vector3D color, TextAlignment alignment = TextAlignment::LEFT);

    void Draw(RendererOpenGl& renderer) override;

    void SetText(std::string pText);

private:
    std::string mText;
    float mScale;
    Vector3D mColor;
    TextAlignment mAlignment;
};

