#pragma once

#include "Vector2D.h"
#include "Vector3D.h"
#include "Matrix4DRow.h"
#include "Shaders/ShaderProgram.h"
#include "Window.h"
#include "TextAlignementEnum.h"
#include <map>

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    unsigned int TextureID = 0;            // ID handle of the glyph texture
    Vector2D Size = Vector2D::Zero;        // Size of glyph
    Vector2D Bearing = Vector2D::Zero; ;   // Offset from baseline to left/top of glyph
    unsigned int Advance = 0;              // Horizontal offset to advance to next glyph
};

class TextRenderer
{
public:
    static TextRenderer& Instance();

	bool Init(Window& pWindow);
    void RenderText(std::string text, float x, float y, float scale, Vector3D color, TextAlignment alignment);
    float ComputeTextWidth(const std::string& text, float scale);
private:
    ~TextRenderer();
    TextRenderer() = default;
    TextRenderer(const TextRenderer&) = delete;
    TextRenderer& operator=(const TextRenderer&) = delete;
    std::map<GLchar, Character> mCharacters;
    unsigned int VAO, VBO;	
    Shader mVertexShader, mFragmentShader;
    ShaderProgram mShaderProgram;
};

