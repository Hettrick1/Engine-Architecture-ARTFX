#pragma once

#include <vector>
#include "Shaders/Shader.h"
#include "Shaders/ShaderProgram.h"

class Texture;
class VertexArray;


class Mesh
{
public:
	Mesh();
	~Mesh();

	void Unload();

	void AddTexture(Texture* pTexture);

	void SetShaderProgram(ShaderProgram pShaderProgram);
	void SetVertexShader(Shader pVertexShader);
	void SetFragmentShader(Shader pFragmentShader);

	VertexArray* GetVao() const
	{
		return mVao;
	}
	ShaderProgram& GetShaderProgram();
	Shader& GetVertexShader();
	Shader& GetFragmentShader();
	Texture* GetTexture(unsigned int pTextureIndex);

private:
	std::vector<Texture*> mTextures;
	VertexArray* mVao;
	Shader mVertexShader, mFragmentShader;
	ShaderProgram mShaderProgram;
};

