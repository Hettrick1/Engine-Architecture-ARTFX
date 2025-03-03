#pragma once

#include "SpriteComponent.h"

class FlipbookComponent : public SpriteComponent
{
public:
	FlipbookComponent(Actor* pOwner, const std::vector<Texture*>& pTextures, int pDrawOrder = 100);
	virtual ~FlipbookComponent();
	FlipbookComponent() = delete;
	FlipbookComponent(const FlipbookComponent&) = delete;
	FlipbookComponent& operator=(const FlipbookComponent&) = delete;
public:
	float GetAnimationFps() const { return mAnimationFps; }
	void SetAnimationTextures(const std::vector<Texture*>& pTextures);
	void SetAnimationFps(float pFps);

	void Update() override;
private:
	std::vector<Texture*> mAnimationTextures;
	float mCurrentFrame;
	float mAnimationFps;
};

