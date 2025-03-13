#pragma once
#include "Actor.h"
class BowlingPlayer : public Actor
{
public:
	BowlingPlayer();
	~BowlingPlayer();
	void Start() override;
	void Update() override;
	void Destroy() override;
private:

};

