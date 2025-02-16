#pragma once
#include "Actor.h"
#include "IActionListener.h"
#include "FlipbookComponent.h"

class SpaceInvaderPlayer : public Actor
{
public:
	SpaceInvaderPlayer();
	~SpaceInvaderPlayer();
	void Start() override;
	void Update() override;
	void Destroy() override;
private:
};

