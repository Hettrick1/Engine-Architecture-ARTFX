#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Maths.h"

class MeshComponent : public Component
{
public:
	MeshComponent(Actor* pOwner);
	virtual ~MeshComponent();
	virtual void Draw(Matrix4DRow viewProj);
	virtual void SetMesh(Mesh& pMesh);
	void SetTextureIndex(unsigned int pTextureIndex);
protected:
	Mesh* mMesh;
	unsigned int mTextureIndex;
};

