#pragma once

#include "IRenderer.h"
#include "VertexArray.h"
#include "Shaders/ShaderProgram.h"
#include "DebugLine.h"
#include <vector>
#include "DebugRenderer.h"
#include "SkySphereComponent.h"

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
	void Unload() override;

	void AddSprite(SpriteComponent* pSprite) override;
	void RemoveSprite(SpriteComponent* pSprite) override;

	void AddMesh(MeshComponent* pMesh) override;
	void RemoveMesh(MeshComponent* pMesh) override;

	void AddSkySphere(SkySphereComponent* pSkySphere) override;
	void RemoveSkySphere() override;

	void AddDebugCollider(ColliderComponent* pCol) override;
	void AddDebugLine(DebugLine* pLine) override;

	void SetViewMatrix(Matrix4DRow pViewMatrix) override;

	void DrawSprite(Actor& pActor, Texture& pTexture, Rectangle pRect, Vector2D pOrigin, IRenderer::Flip pFlipMethod) const override;
	void DrawDebugBox(Vector3D& pMin, Vector3D& pMax, Matrix4DRow pWorldTransform) override;
	void DrawDebugLine(const Vector3D& start, const Vector3D& end, const HitResult& hit) override;

	void DrawSkySphere();
	void DrawMeshes();
	void DrawSprites();
	void DrawHud();
	void DrawHudImage(Texture& pTexture, Rectangle pRect, Vector2D pOrigin, Vector4D pTint);

	void SetSpriteShaderProgram(ShaderProgram& shaderProgram) override;

	void SetHud(HudManager* pHud) override;
	inline HudManager* GetHud() const override { return mHud; }

	RendererType GetType() const override { return IRenderer::RendererType::OPENGL; }
	DebugRenderer* GetDebugRenderer() const override { return mDebugRenderer; }

	void SetWireFrameMode(bool pWireframe) override;
	inline bool GetWireFrame() const override { return mWireFrameMode; }

private:
	Window* mWindow;
	VertexArray* mVAO;
	SDL_GLContext mContext;
	std::vector<SpriteComponent*> mSprites;
	std::vector<MeshComponent*> mMeshes;
	ShaderProgram* mSpriteShaderProgram;
	Matrix4DRow mSpriteViewProj;
	Matrix4DRow mView, mProj;
	Shader mSpriteVertexShader;
	Shader mSpriteFragmentShader;
	ShaderProgram mSpriteShaderProgramTemp;
	HudManager* mHud;
	DebugRenderer* mDebugRenderer;
	bool mWireFrameMode;
	SkySphereComponent* mSkySphereComponent;
};