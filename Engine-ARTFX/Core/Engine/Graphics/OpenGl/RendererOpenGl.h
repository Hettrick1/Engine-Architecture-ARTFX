#pragma once

#include "IRenderer.h"
#include "VertexArray.h"
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

	void DrawSprite(Actor& pActor, Texture& pTexture, Rectangle pRect, Vector2D pOrigin, IRenderer::Flip pFlipMethod) const override;

	RendererType GetType() override { return IRenderer::RendererType::OPENGL; }
private:
	Window* mWindow;
	VertexArray* mVAO;
	SDL_GLContext mContext;
	std::vector<SpriteComponent*> mSprites;
};