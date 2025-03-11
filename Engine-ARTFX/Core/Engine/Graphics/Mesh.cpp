#include "Mesh.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Assets.h"

Mesh::Mesh()
	: mVao(nullptr)
{
	mVertexShader.Load("BasicMesh.vert", ShaderType::VERTEX);
	mFragmentShader.Load("BasicMesh.frag", ShaderType::FRAGMENT);
	mShaderProgram.Compose({ &mVertexShader, &mFragmentShader });
	mTextures.emplace_back(&Assets::GetTexture("cube"));
	mTextures.emplace_back(&Assets::GetTexture("walk1"));
}

Mesh::Mesh(std::vector<Vertex> pVertices)
	: mVertices(std::move(pVertices)), mVao(nullptr)
{
	mVao = new VertexArray(ToVerticeArray(), mVertices.size());
	mVertexShader.Load("BasicMesh.vert", ShaderType::VERTEX);
	mFragmentShader.Load("BasicMesh.frag", ShaderType::FRAGMENT);
	mShaderProgram.Compose({ &mVertexShader, &mFragmentShader });
	mTextures.emplace_back(&Assets::GetTexture("cube"));
	mTextures.emplace_back(&Assets::GetTexture("walk1"));
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

float* Mesh::ToVerticeArray()
{
	float* array = new float[mVertices.size() * 8];
	int counter = 0;
	for (int i = 0; i < mVertices.size(); i++)
	{
		array[counter + 0] = mVertices[i].position.x;
		array[counter + 1] = mVertices[i].position.y;
		array[counter + 2] = mVertices[i].position.z;
		array[counter + 3] = mVertices[i].normal.x;
		array[counter + 4] = mVertices[i].normal.y;
		array[counter + 5] = mVertices[i].normal.z;
		array[counter + 6] = mVertices[i].texCoord.x;
		array[counter + 7] = mVertices[i].texCoord.y;
		counter += 8;
	}
	return array;
}
