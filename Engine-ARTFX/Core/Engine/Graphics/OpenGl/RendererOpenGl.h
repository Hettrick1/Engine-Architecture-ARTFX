#pragma once

#include "IRenderer.h"
#include "VertexArray.h"
#include "Shaders/ShaderProgram.h"
#include "IRenderer.h"
#include <vector>
#include <vector>

class Actor;
class Texture;

class RendererOpenGl : public IRenderer
{
public:
	RendererOpenGl();
	virtual ~RendererOpenGl();
	RendererOpenGl(const RendererOpenGl&) = delete;
	RendererOpenGl& operator=(const RendererOpenGl&) = delete;

	bool Initialize(Window& pWindow) override;
	void BeginDraw() override;
	void Draw() override;
	void EndDraw() override;
	void Close() override;

	void AddSprite(SpriteComponent* pSprite) override;
	void RemoveSprite(SpriteComponent* pSprite) override;

	void AddMesh(MeshComponent* pMesh) override;
	void RemoveMesh(MeshComponent* pMesh) override;

	void AddDebugCollider(ColliderComponent* pCol) override;

	void SetViewMatrix(Matrix4DRow pViewMatrix) override;

	void DrawSprite(Actor& pActor, Texture& pTexture, Rectangle pRect, Vector2D pOrigin, IRenderer::Flip pFlipMethod) const override;
	void DrawDebugBox(Vector3D& pMin, Vector3D& pMax, Matrix4DRow pWorldTransform) override;

	void DrawMeshes();
	void DrawSprites();

	void SetSpriteShaderProgram(ShaderProgram& shaderProgram) override;

	RendererType GetType() override { return IRenderer::RendererType::OPENGL; }
private:
	Window* mWindow;
	VertexArray* mVAO;
	SDL_GLContext mContext;
	std::vector<SpriteComponent*> mSprites;
	std::vector<MeshComponent*> mMeshes;
	std::vector<ColliderComponent*> mCollider;
	ShaderProgram* mSpriteShaderProgram;
	ShaderProgram mDebugShaderProgram;
	Matrix4DRow mSpriteViewProj;
	Matrix4DRow mView, mProj;
	Shader mSpriteVertexShader;
	Shader mSpriteFragmentShader;
	ShaderProgram mSpriteShaderProgramTemp;
};