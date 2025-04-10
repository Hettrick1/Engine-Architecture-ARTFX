#pragma once
#include "Component.h"
#include "../Graphics/Texture.h"
#include "Mesh.h"
#include "Maths.h"
#include "CubeTextureMap.h"

class SkySphereComponent : public Component
{
public:
	SkySphereComponent(Actor* pOwner, bool isSphere = false, std::vector<std::string> textures = {}, ShaderProgram* pProgram = nullptr);
	virtual ~SkySphereComponent();
	virtual void Draw(Matrix4DRow viewProj);
	virtual void SetMesh(Mesh& pMesh);
	void SetTextureIndex(unsigned int pTextureIndex);
	inline Mesh* GetMesh() const { return mMesh; }

	void SetShaderProgram(ShaderProgram pShaderProgram);

	inline ShaderProgram& GetShaderProgram() { return mShaderProgram; }
	inline CubeTextureMap& GetCubeMap() { return mCubeMap; }
	inline unsigned int& GetTextureIndex() { return mTextureIndex; }
	inline VertexArray* GetVao() const { return mVao; }
	inline GLenum& GetTextureType() { return mTextureType; }

	void SetTiling(Vector2D pTiling);

	static int index;

protected:
	Mesh* mMesh;
	Shader mVertexShader, mFragmentShader, mTessellationControlShader, mTessellationEvalShader;
	ShaderProgram mShaderProgram;
	CubeTextureMap mCubeMap;
	Vector2D mTiling;
	unsigned int mTextureIndex;
	bool mIsSphere;
	VertexArray* mVao;
	GLenum mTextureType;
	std::vector<std::string> mTextureToLoad;
};