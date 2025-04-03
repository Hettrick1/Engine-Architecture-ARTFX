#pragma once

#include "IRenderer.h"
#include "VertexArray.h"
#include "Shaders/ShaderProgram.h"
#include "Window.h"
#include "Matrix4DRow.h"

class DebugRenderer
{
public:
	DebugRenderer();
	~DebugRenderer();

	void Initialize(Window& pWindow);

	void Draw(IRenderer& pRenderer);

	void AddDebugCollider(ColliderComponent* pCol);
	void AddDebugLine(DebugLine* pLine);

	void DrawDebugBox(Vector3D& pMin, Vector3D& pMax, Matrix4DRow pWorldTransform);
	void DrawDebugLine(const Vector3D& start, const Vector3D& end, const HitResult& hit);

	void SetViewMatrix(Matrix4DRow pViewMatrix);

private:
	Shader mDebugVertex;
	Shader mDebugFragment;
	ShaderProgram mDebugShaderProgram;
	Matrix4DRow mView, mProj;
	std::vector<ColliderComponent*> mCollider;
	std::vector<DebugLine*> mLines;
	GLuint mDebugBoxVao, mDebugBoxVbo, mDebugLineVao, mDebugLineVbo;
};
