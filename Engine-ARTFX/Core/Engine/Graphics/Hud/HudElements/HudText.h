#pragma once
#include "HudElement.h"
#include "TextRenderer.h"
#include "RendererOpenGl.h"

class HudText :
    public HudElement
{
public:
    HudText(const std::string& text, float x, float y, float scale, Vector3D color);

    void Draw(RendererOpenGl& renderer) override;

private:
    std::string mText;
    float mScale;
    Vector3D mColor;
};

