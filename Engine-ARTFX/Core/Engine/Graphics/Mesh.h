#pragma once

#include <vector>
#include "Shaders/Shader.h"
#include "Shaders/ShaderProgram.h"
#include "Vertex.h"

class Texture;
class VertexArray;


class Mesh
{
public:
	Mesh();
	Mesh(std::vector<Vertex> pVertices);
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
	float* ToVerticeArray();

	void SetTextureTiling(Vector2D pTextureTiling);
	Vector2D GetTextureTiling() const { return mTextureTiling; }

private:
	std::vector<Texture*> mTextures;
	std::vector<Vertex> mVertices;
	VertexArray* mVao;
	Shader mVertexShader, mFragmentShader;
	ShaderProgram mShaderProgram;
	Vector2D mTextureTiling;
};

