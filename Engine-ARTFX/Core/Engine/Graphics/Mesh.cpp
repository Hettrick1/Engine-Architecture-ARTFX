#include "Mesh.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Assets.h"
#include "Scene.h"

Mesh::Mesh()
	: mVao(nullptr)
{
}

Mesh::Mesh(std::vector<Vertex> pVertices)
	: mVertices(std::move(pVertices)), mVao(nullptr)
{
	Assets::LoadTexture(*(Scene::ActiveScene->GetRenderer()), "Imports/Sprites/planks.png", "cube");
	mVao = new VertexArray(ToVerticeArray(), mVertices.size());
	mVertexShader.Load("BasicMesh.vert", ShaderType::VERTEX);
	mFragmentShader.Load("BasicMesh.frag", ShaderType::FRAGMENT);
	mShaderProgram.Compose({ &mVertexShader, &mFragmentShader });
	mTextures.emplace_back(&Assets::GetTexture("cube"));
	mTextureTiling = Vector2D(1, 1);
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
	if (mVertices.empty()) return nullptr;

	float* array = new float[mVertices.size() * 8];
	for (size_t i = 0; i < mVertices.size(); i++)
	{
		size_t index = i * 8;
		array[index + 0] = mVertices[i].position.x;
		array[index + 1] = mVertices[i].position.z;// inverser y et z car le up est diff�rent
		array[index + 2] = mVertices[i].position.y;
		array[index + 3] = mVertices[i].normal.x;
		array[index + 4] = mVertices[i].normal.z;
		array[index + 5] = mVertices[i].normal.y;
		array[index + 6] = mVertices[i].texCoord.x;
		array[index + 7] = -mVertices[i].texCoord.y;
	}
	return array;
}

void Mesh::SetTextureTiling(Vector2D pTextureTiling)
{
	mTextureTiling = pTextureTiling;
}
