#pragma once
#include "Actor.h"
#include "IActionListener.h"

class SpaceInvaderPlayer : public Actor, IActionListener
{
public:
	SpaceInvaderPlayer();
	~SpaceInvaderPlayer();
	void Start() override;
	void Update() override;
	void Destroy() override;

	void OnActionTriggered(InputActions* action) override;
private:

};

