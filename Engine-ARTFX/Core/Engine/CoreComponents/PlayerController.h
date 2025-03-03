#pragma once

#include "ActorMovementComponent.h"
#include "IActionListener.h"

class PlayerController : public ActorMovementComponent, IActionListener
{
public:
	PlayerController(Actor* pOwner, int pUpdateOrder = 100);
	PlayerController() = delete;
	PlayerController(const PlayerController&) = delete;
	PlayerController& operator=(const PlayerController&) = delete;
public:
	void OnActionStarted(InputActions* action) override;
	void OnActionTriggered(InputActions* action) override;
	void OnActionEnded(InputActions* action) override;
public:
	void Update() override;
public:
	void EnableDirection(Vector2D pDirection);
	void DisableDirection(Vector2D pDirection);
private:
	bool mCanGoRight, mCanGoLeft, mCanGoUp, mCanGoDown;
};

