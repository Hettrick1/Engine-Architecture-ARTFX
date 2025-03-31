#include "DoomPC.h"

#include "BooleanActions.h"
#include "InputAxis2D.h"
#include "InputManager.h"
#include "Actor.h"
#include "Log.h"
#include "Timer.h"
#include "CameraComponent.h"

DoomPC::DoomPC(Actor* pOwner, int pUpdateOrder)
	: Component(pOwner, pUpdateOrder), playerRbRef(nullptr)
{
	InputManager& inputManager = InputManager::Instance();
	inputManager.CreateNewAxis2DBinding(this, "movement", SDLK_d, SDLK_a, SDLK_w, SDLK_s);
	/*inputManager.CreateNewBooleanBinding(this, "up", SDLK_SPACE);
	inputManager.CreateNewBooleanBinding(this, "down", SDLK_LSHIFT);
	inputManager.CreateNewBooleanBinding(this, "forward", SDLK_w);
	inputManager.CreateNewBooleanBinding(this, "left", SDLK_a);
	inputManager.CreateNewBooleanBinding(this, "backward", SDLK_s);
	inputManager.CreateNewBooleanBinding(this, "right", SDLK_d);*/
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
	if (action->GetType() == ActionType::Axis2D)
	{
		InputAxis2D* Triggeredaction = static_cast<InputAxis2D*>(action);
		if (Triggeredaction && Triggeredaction->GetName() == "movement")
		{
			Vector2D axis = Triggeredaction->GetAxis();
			Vector3D forward = mOwner->GetComponentOfType<CameraComponent>()->GetWorldTransform().GetXAxis();
			playerRbRef->SetVelocity(Vector3D(axis.x * 3, axis.y * 3, 0) * forward);
		}
	}
}

void DoomPC::OnActionTriggered(InputActions* action)
{
	if (action->GetType() == ActionType::Axis2D)
	{
		InputAxis2D* Triggeredaction = static_cast<InputAxis2D*>(action);
		if (Triggeredaction && Triggeredaction->GetName() == "Mouse")
		{
			SDL_SetRelativeMouseMode(SDL_TRUE);
			SDL_SetHintWithPriority(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1", SDL_HINT_OVERRIDE);
			Vector2D axis = Triggeredaction->GetAxis();

			float sensitivity = 0.1f;
			axis.x *= sensitivity;
			mOwner->GetTransformComponent().RotateZ(axis.x);
		}
		if (Triggeredaction && Triggeredaction->GetName() == "movement")
		{
			Vector2D axis = Triggeredaction->GetAxis();
			Vector3D forward = mOwner->GetComponentOfType<CameraComponent>()->GetWorldTransform().GetYAxis();
			Vector3D right = mOwner->GetComponentOfType<CameraComponent>()->GetWorldTransform().GetXAxis();

			Vector3D moveDirection = forward * axis.y + right * -axis.x;
			playerRbRef->SetVelocity(moveDirection * 3);
		}
	}
}

void DoomPC::OnActionEnded(InputActions* action)
{
}

void DoomPC::Update()
{
	if (playerRbRef == nullptr)
	{
		playerRbRef = mOwner->GetRigidBody();
		Log::Info("Rigidboy not set in the player controller");
	}
}
