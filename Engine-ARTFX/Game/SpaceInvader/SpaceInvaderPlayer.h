#pragma once

#include "Actor.h"

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

