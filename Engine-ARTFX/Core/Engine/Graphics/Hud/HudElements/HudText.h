#pragma once
#include "HudElement.h"
#include "TextRenderer.h"
#include "RendererOpenGl.h"
#include "TextAlignementEnum.h"

class HudText :
    public HudElement
{
public:
    HudText(const std::string& text, float x, float y, float scale, Vector4D color,TextAlignment alignment = TextAlignment::LEFT, Font* pFont = nullptr);
    ~HudText();

    void Draw(RendererOpenGl& renderer) override;

    void SetText(std::string pText);
    void SetColor(Vector4D color);

    inline Vector4D GetColor() const { return mColor; }

    void SetShaderProgram(ShaderProgram* pShaderProgram);

private:
    std::string mText;
    float mScale;
    Vector4D mColor;
    TextAlignment mAlignment;
    Font* mFont;
    ShaderProgram* mShaderProgram;
};

