#include "MeshComponent.h"
#include "Scene.h"
#include "IRenderer.h"
#include "Actor.h"
#include "VertexArray.h"

MeshComponent::MeshComponent(Actor* pOwner)
	: Component(pOwner), mMesh(nullptr), mTextureIndex(0)
{
	mMesh = new Mesh();
	mOwner->GetScene().GetRenderer()->AddMesh(this);
}

MeshComponent::~MeshComponent()
{
	mOwner->GetScene().GetRenderer()->RemoveMesh(this);
}

void MeshComponent::Draw(Matrix4DRow viewProj)
{
	if (mMesh)
	{
		Matrix4DRow wt = mOwner->GetTransformComponent().GetWorldTransform();
		mMesh->GetShaderProgram().Use();
		mMesh->GetShaderProgram().setMatrix4Row("uViewProj", viewProj);
		mMesh->GetShaderProgram().setMatrix4Row("uWorldTransform", wt);
		Texture* tex = mMesh->GetTexture(mTextureIndex);
		if (tex)
		{
			tex->SetActive();
		}
		mMesh->GetVao()->SetActive();
		glDrawElements(GL_TRIANGLES, mMesh->GetVao()->GetIndicesCount(), GL_UNSIGNED_INT, 0);
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
