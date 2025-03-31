#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Maths.h"

class MeshComponent : public Component
{
public:
	MeshComponent(Actor* pOwner, Mesh* pMesh);
	virtual ~MeshComponent();
	virtual void Draw(Matrix4DRow viewProj);
	virtual void SetMesh(Mesh& pMesh);
	void SetTextureIndex(unsigned int pTextureIndex);
	inline Mesh* GetMesh() const { return mMesh; }
protected:
	Mesh* mMesh;
	unsigned int mTextureIndex;
};

