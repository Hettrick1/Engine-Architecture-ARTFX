#include "MeshComponent.h"
#include "Scene.h"
#include "IRenderer.h"
#include "Actor.h"
#include "VertexArray.h"
#include "Vertex.h"

MeshComponent::MeshComponent(Actor* pOwner, Mesh* pMesh, ShaderProgram* pProgram)
	: Component(pOwner), mMesh(pMesh), mTextureIndex(0)
{
	mOwner->GetScene().GetRenderer()->AddMesh(this);
	if (pProgram == nullptr)
	{
		mVertexShader.Load("BasicMesh.vert", ShaderType::VERTEX);
		mFragmentShader.Load("BasicMesh.frag", ShaderType::FRAGMENT);
		mShaderProgram.Compose({ &mVertexShader, &mFragmentShader });
	}
	else {
		mShaderProgram = *pProgram;
	}
}

MeshComponent::~MeshComponent()
{
}

void MeshComponent::Draw(Matrix4DRow viewProj)
{
	if (mMesh)
	{
		Matrix4DRow wt = mOwner->GetTransformComponent().GetWorldTransform();
		mShaderProgram.Use();
		mShaderProgram.setMatrix4Row("uViewProj", viewProj);
		mShaderProgram.setMatrix4Row("uWorldTransform", wt);
		mShaderProgram.setVector2f("uTiling", mMesh->GetTextureTiling());
		Texture* tex = mMesh->GetTexture(mTextureIndex);
		if (tex)
		{
			tex->SetActive();
		}
		mMesh->GetVao()->SetActive();
		if ((mShaderProgram.GetType() & ShaderProgramType::TESSELLATION_CONTROL) != 0)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glPatchParameteri(GL_PATCH_VERTICES, 3);
			glDrawArrays(GL_PATCHES, 0, mMesh->GetVao()->GetVerticeCount());
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, mMesh->GetVao()->GetVerticeCount());
		}
	}
}

void MeshComponent::SetMesh(Mesh& pMesh)
{
	mMesh = &pMesh;
}

void MeshComponent::SetTextureIndex(unsigned int pTextureIndex)
{
	mTextureIndex = pTextureIndex;
}

void MeshComponent::SetShaderProgram(ShaderProgram pShaderProgram)
{
	mShaderProgram = pShaderProgram;
}
