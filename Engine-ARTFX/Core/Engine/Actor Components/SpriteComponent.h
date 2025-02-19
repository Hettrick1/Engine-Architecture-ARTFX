#pragma once
#include "Component.h"
#include "../Graphics/Texture.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(Actor* pOwner, Texture& pTexture, int pDrawOrder = 100, Vector2D pSizeOverride = 0);
	virtual ~SpriteComponent();
	SpriteComponent() = delete;
	SpriteComponent(const SpriteComponent&) = delete;
	SpriteComponent& operator= (const SpriteComponent&) = delete;

	virtual void SetTexture(const Texture& pTexture);
	void SetFlipMethode(Renderer::Flip pFlipMethode);
	virtual void Draw(Renderer& pRenderer);

	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexWidth() const { return mTexWidth; }
	int GetTexHeight() const { return mTexHeight; }
protected:
	Texture mTexture;
	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
	int mTexWidthOverride;
	int mTexHeightOverride;
	Renderer::Flip mFlipMethode;
};

