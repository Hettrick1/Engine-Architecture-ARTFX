#include "Mesh.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Assets.h"

Mesh::Mesh()
	: mVao(nullptr)
{
	mVao = new VertexArray(cubeVertices, 28, cubeIndices, 36);
	mVertexShader.Load("BasicMesh.vert", ShaderType::VERTEX);
	mFragmentShader.Load("BasicMesh.frag", ShaderType::FRAGMENT);
	mShaderProgram.Compose({ &mVertexShader, &mFragmentShader });
	mTextures.emplace_back(&Assets::GetTexture("cube"));
	mTextures.emplace_back(&Assets::GetTexture("player"));
}

Mesh::~Mesh()
{
	Unload();
}

void Mesh::Unload()
{
	if (mVao != nullptr) {
		delete mVao;
	}
	mVao = nullptr;
}

void Mesh::AddTexture(Texture* pTexture)
{
	mTextures.push_back(pTexture);
}

void Mesh::SetShaderProgram(ShaderProgram pShaderProgram)
{
	mShaderProgram = pShaderProgram;
}

void Mesh::SetVertexShader(Shader pVertexShader)
{
	mVertexShader = pVertexShader;
}

void Mesh::SetFragmentShader(Shader pFragmentShader)
{
	mFragmentShader = pFragmentShader;
}

ShaderProgram& Mesh::GetShaderProgram()
{
	return mShaderProgram;
}

Shader& Mesh::GetVertexShader()
{
	return mVertexShader;
}

Shader& Mesh::GetFragmentShader()
{
	return mFragmentShader;
}

Texture* Mesh::GetTexture(unsigned int pTextureIndex)
{
	return mTextures[pTextureIndex];
}
