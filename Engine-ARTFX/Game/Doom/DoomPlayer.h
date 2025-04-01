#pragma once

#include "FlipbookComponent.h"
#include "Actor.h"
#include "HudElements/HudText.h"
#include "HudElements/HudImage.h"

class DoomPlayer : public Actor
{
public:
	DoomPlayer();
	~DoomPlayer();
	void Start() override;
	void Update() override;
	void Destroy() override;
private:
	FlipbookComponent* mGun;
	HudText* mFpsText;
	HudText* mGunAmoText;
	HudText* mHealthText;
	HudText* mArmorText;
	HudImage* mWeaponIconImage;
	int mGunAmo;
	int mHealth;
	int mArmor;
};

