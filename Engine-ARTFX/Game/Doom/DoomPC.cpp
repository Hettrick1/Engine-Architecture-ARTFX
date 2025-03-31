#include "DoomPC.h"

#include "PlayerController3D.h"
#include "BooleanActions.h"
#include "InputAxis2D.h"
#include "InputManager.h"
#include "Actor.h"
#include "Log.h"
#include "CameraComponent.h"
#include "Timer.h"


DoomPC::DoomPC(Actor* pOwner, int pUpdateOrder)
	: Component(pOwner, pUpdateOrder), playerRbRef(nullptr)
{
	InputManager& inputManager = InputManager::Instance();
	inputManager.CreateNewBooleanBinding(this, "up", SDLK_SPACE);
	inputManager.CreateNewBooleanBinding(this, "down", SDLK_LSHIFT);
	inputManager.CreateNewBooleanBinding(this, "forward", SDLK_w);
	inputManager.CreateNewBooleanBinding(this, "left", SDLK_a);
	inputManager.CreateNewBooleanBinding(this, "backward", SDLK_s);
	inputManager.CreateNewBooleanBinding(this, "right", SDLK_d);
	inputManager.CreateNewAxis2DBinding(this, "Mouse");
	if (playerRbRef == nullptr)
	{
		playerRbRef = mOwner->GetRigidBody();
	}
}

DoomPC::~DoomPC()
{
	if (playerRbRef != nullptr)
	{
		delete playerRbRef;
		playerRbRef = nullptr;
	}
}

void DoomPC::OnActionStarted(InputActions* action)
{
}

void DoomPC::OnActionTriggered(InputActions* action)
{
}

void DoomPC::OnActionEnded(InputActions* action)
{
}

void DoomPC::Update()
{
	if (playerRbRef == nullptr)
	{
		playerRbRef = mOwner->GetRigidBody();
		Log::Error(LogType::Game,"Rigidboy not set in the player controller");
	}
	else
	{
		Log::Info("Rigidboy referenced in the PC ");
	}
}
