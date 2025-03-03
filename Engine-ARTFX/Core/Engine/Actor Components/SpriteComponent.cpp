#include "SpriteComponent.h"

#include "Actor.h"
#include "../../Scenes/Scene.h"

SpriteComponent::SpriteComponent(Actor* pOwner, Texture& pTexture, int pDrawOrder, Vector2D pSizeOverride)
	: Component(pOwner), mTexture(pTexture), mDrawOrder(pDrawOrder), mFlipMethode(IRenderer::Flip::None)
{
	if (pSizeOverride.x == 0 || pSizeOverride.y == 0) {
		mTexWidth = static_cast<int>(pTexture.GetTextureSize().x);
		mTexHeight = static_cast<int>(pTexture.GetTextureSize().y);
	}
	else {
		mTexWidthOverride = static_cast<int>(pSizeOverride.x);
		mTexHeightOverride = static_cast<int>(pSizeOverride.y);
		mTexWidth = mTexWidthOverride;
		mTexHeight = mTexHeightOverride;
	}

	mOwner->GetScene().GetRenderer()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetScene().GetRenderer()->RemoveSprite(this);
}

void SpriteComponent::SetTexture(const Texture& pTexture)
{
	mTexture = pTexture;
	if (mTexHeightOverride == 0 || mTexWidthOverride == 0)
	{
		mTexture.UpdateInfo(mTexWidth, mTexHeight);
	}
	else 
	{
		mTexWidth = mTexWidthOverride;
		mTexHeight = mTexHeightOverride;
		mTexture.OverrideTextureSize(mTexWidth, mTexHeight);
	}
}

void SpriteComponent::SetFlipMethode(IRenderer::Flip pFlipMethode)
{
	mFlipMethode = pFlipMethode;
}

void SpriteComponent::Draw(IRenderer& pRenderer)
{
	if (mTexHeightOverride != 0 && mTexWidthOverride != 0)
	{
		mTexture.OverrideTextureSize(mTexWidthOverride, mTexHeightOverride);
	}
	Vector2D origin = { ((mTexWidth * mOwner->GetTransformComponent().GetSize().x) / 2.0f),
		((mTexHeight * mOwner->GetTransformComponent().GetSize().y) / 2.0f) };
	pRenderer.DrawSprite(*mOwner, mTexture, Rectangle(), origin, mFlipMethode);
}

Texture& SpriteComponent::GetTexture()
{
	return mTexture;
}
