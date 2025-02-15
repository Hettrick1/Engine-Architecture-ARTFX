#pragma once
#include "Actor.h"
#include "IActionListener.h"
#include "FlipbookComponent.h"

class SpaceInvaderPlayer : public Actor, IActionListener
{
public:
	SpaceInvaderPlayer();
	~SpaceInvaderPlayer();
	void Start() override;
	void Update() override;
	void Destroy() override;

	void OnActionStarted(InputActions* action) override;
	void OnActionTriggered(InputActions* action) override;
	void OnActionEnded(InputActions* action) override;
private:
	FlipbookComponent* mWalkAnim;
};

