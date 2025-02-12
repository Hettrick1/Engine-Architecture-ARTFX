#include "SpriteComponent.h"

#include "Actor.h"
#include "../../Scenes/Scene.h"

SpriteComponent::SpriteComponent(Actor* pOwner, Texture& pTexture, int pDrawOrder)
	: Component(pOwner), mTexture(pTexture), mDrawOrder(pDrawOrder), mTexWidth(pTexture.GetTextureSize().x), mTexHeight(pTexture.GetTextureSize().y)
{
	mOwner->GetScene().GetRenderer()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetScene().GetRenderer()->RemoveSprite(this);
}

void SpriteComponent::SetTexture(const Texture& pTexture)
{
	mTexture = pTexture;
	mTexture.UpdateInfo(mTexWidth, mTexHeight);
}

void SpriteComponent::Draw(Renderer& pRenderer)
{
	Vector2D origin{((mTexWidth * mOwner->GetTransformComponent().GetSize().x) / 2.0f), 
		((mTexHeight * mOwner->GetTransformComponent().GetSize().y) / 2.0f) };
	pRenderer.DrawSprite(*mOwner, mTexture, Rectangle(), origin, Renderer::Flip::None);
}
