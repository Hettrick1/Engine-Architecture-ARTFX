#include "MeshComponent.h"
#include "Scene.h"
#include "IRenderer.h"
#include "Actor.h"
#include "VertexArray.h"
#include "Vertex.h"

MeshComponent::MeshComponent(Actor* pOwner, Mesh* pMesh)
	: Component(pOwner), mMesh(pMesh), mTextureIndex(0)
{
	mOwner->GetScene().GetRenderer()->AddMesh(this);
}

MeshComponent::~MeshComponent()
{
}

void MeshComponent::Draw(Matrix4DRow viewProj)
{
	if (mMesh)
	{
		Matrix4DRow wt = mOwner->GetTransformComponent().GetWorldTransform();
		mMesh->GetShaderProgram().Use();
		mMesh->GetShaderProgram().setMatrix4Row("uViewProj", viewProj);
		mMesh->GetShaderProgram().setMatrix4Row("uWorldTransform", wt);
		mMesh->GetShaderProgram().setVector2f("uTiling", mMesh->GetTextureTiling());
		Texture* tex = mMesh->GetTexture(mTextureIndex);
		if (tex)
		{
			tex->SetActive();
		}
		mMesh->GetVao()->SetActive();
		if (mMesh->GetShaderProgram().GetType() & (ShaderProgramType::TESSELLATION_CONTROL + ShaderProgramType::TESSELLATION_EVALUATION))
		{
			glPointSize(5.0f);
			glDrawArrays(GL_PATCHES, 0, 3);
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
