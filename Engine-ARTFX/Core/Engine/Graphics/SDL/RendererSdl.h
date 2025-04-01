#pragma once

#include "IRenderer.h"
#include <vector>

class Actor;
class Texture;

class RendererSdl : public IRenderer
{
public:
	RendererSdl();
	RendererSdl(const RendererSdl&) = delete;
	RendererSdl& operator = (const RendererSdl&) = delete;

	bool Initialize(Window& rWindow);
	void BeginDraw() override;
	void Draw() override;
	void EndDraw() override;
	void Close() override;

	void AddSprite(SpriteComponent* pSprite) override;
	void RemoveSprite(SpriteComponent* pSprite) override;

	RendererType GetType() const override { return IRenderer::RendererType::SDL; }

	void DrawRect(Rectangle& rRect);
	void DrawSprite(Actor& pActor, Texture& pTexture, Rectangle pRect, Vector2D pOrigin, IRenderer::Flip pFlipMethod) const override;
	SDL_Renderer* ToSdlRenderer() override;
private:
	SDL_Renderer* mSdlRenderer;
	std::vector<SpriteComponent*> mSprites;
};

