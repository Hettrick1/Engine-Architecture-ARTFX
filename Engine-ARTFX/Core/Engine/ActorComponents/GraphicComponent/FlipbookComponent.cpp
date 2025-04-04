#include "FlipbookComponent.h"

#include "Timer.h"

FlipbookComponent::FlipbookComponent(Actor* pOwner, const std::vector<Texture*>& pTextures, int pDrawOrder)
	: SpriteComponent(pOwner, *pTextures[0], pDrawOrder), mCurrentFrame(0.0f), mAnimationFps(24.0f), mHasFinished(true)
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
		mCurrentFrame = 0.0f;
		mPlayOnce = false;
		mHasFinished = true;
	}
}

void FlipbookComponent::SetAnimationFps(float pFps)
{
	mAnimationFps = pFps;
}

void FlipbookComponent::PlayAnimation()
{
	mPlayOnce = true;
}

void FlipbookComponent::Update()
{
	SpriteComponent::Update();
	if (mAnimationTextures.size() == 0) 
	{
		return;
	}
	if (mIsLooping || mPlayOnce)
	{
		mHasFinished = false;
		mCurrentFrame += mAnimationFps * Timer::deltaTime;
		while (mCurrentFrame >= mAnimationTextures.size())
		{
			mCurrentFrame -= mAnimationTextures.size();
			mPlayOnce = false;
			mHasFinished = true;
		}
		SetTexture(*mAnimationTextures[static_cast<int>(mCurrentFrame)]);
	}
}
