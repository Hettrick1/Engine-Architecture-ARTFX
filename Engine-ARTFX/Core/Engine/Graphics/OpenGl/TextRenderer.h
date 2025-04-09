#pragma once

#include "Vector2D.h"
#include "Vector3D.h"
#include "Matrix4DRow.h"
#include "Shaders/ShaderProgram.h"
#include "Window.h"
#include "TextAlignementEnum.h"
#include <map>
#include "Font.h"

class TextRenderer
{
public:
    static TextRenderer& Instance();

	bool Init(Window& pWindow);
    void RenderText(std::string text, float x, float y, float scale, Vector4D color, Font pFont, TextAlignment alignment, ShaderProgram* pShaderProgram = nullptr);
    float ComputeTextWidth(const std::string& text, float scale, Font pFont);
private:
    ~TextRenderer();
    TextRenderer() = default;
    TextRenderer(const TextRenderer&) = delete;
    TextRenderer& operator=(const TextRenderer&) = delete;
    unsigned int VAO, VBO;
    Window* mWindow;
    Shader mVertexShader, mFragmentShader;
    ShaderProgram mShaderProgram;
    Matrix4DRow mProjection;
};

