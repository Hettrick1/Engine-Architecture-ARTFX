#pragma once

#include "FlipbookComponent.h"
#include "Actor.h"

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
};

