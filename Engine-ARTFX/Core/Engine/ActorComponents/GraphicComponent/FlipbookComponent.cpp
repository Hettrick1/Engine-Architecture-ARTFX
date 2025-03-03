#include "FlipbookComponent.h"

#include "Timer.h"

FlipbookComponent::FlipbookComponent(Actor* pOwner, const std::vector<Texture*>& pTextures, int pDrawOrder)
	: SpriteComponent(pOwner, *pTextures[0], pDrawOrder), mCurrentFrame(0.0f), mAnimationFps(24.0f)
{
	SetAnimationTextures(pTextures);
}

FlipbookComponent::~FlipbookComponent()
{
	while (mAnimationTextures.size() > 0)
	{
		delete mAnimationTextures.back();
		mAnimationTextures.pop_back();
	}
	mAnimationTextures.clear();
}

void FlipbookComponent::SetAnimationTextures(const std::vector<Texture*>& pTextures)
{
	mAnimationTextures = pTextures;
	if (mAnimationTextures.size() > 0) 
	{
		SetTexture(*mAnimationTextures[0]);
	}
}

void FlipbookComponent::SetAnimationFps(float pFps)
{
	mAnimationFps = pFps;
}

void FlipbookComponent::Update()
{
	SpriteComponent::Update();
	if (mAnimationTextures.size() == 0) 
	{
		return;
	}
	mCurrentFrame += mAnimationFps * Timer::deltaTime;
	while (mCurrentFrame >= mAnimationTextures.size())
	{
		mCurrentFrame -= mAnimationTextures.size();
	}
	SetTexture(*mAnimationTextures[static_cast<int>(mCurrentFrame)]);
}
