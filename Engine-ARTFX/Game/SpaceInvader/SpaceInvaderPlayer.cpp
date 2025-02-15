#include "SpaceInvaderPlayer.h"
#include "SpriteComponent.h"
#include "Scene.h"
#include "BooleanActions.h"
#include "InputManager.h"


SpaceInvaderPlayer::SpaceInvaderPlayer() : 
	Actor({500, 500}, 0.5, 0)
{
}

SpaceInvaderPlayer::~SpaceInvaderPlayer()
{
}

void SpaceInvaderPlayer::Start()
{
	Actor::Start();
	Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/pokeball.png", "ball");

	SpriteComponent* sprite = new SpriteComponent(this, Assets::GetTexture("ball"), 500000);

	InputManager& inputManager = InputManager::Instance();
	inputManager.CreateNewBooleanBinding(SDLK_SPACE, this, "jump");
	inputManager.CreateNewBooleanBinding(SDLK_c, this, "shoot");
}

void SpaceInvaderPlayer::Update()
{
	Actor::Update();
}

void SpaceInvaderPlayer::Destroy()
{
	Actor::Destroy();
}

void SpaceInvaderPlayer::OnActionStarted(InputActions* action)
{
	if (action->GetType() == ActionType::Boolean) { 
		auto* jumpAction = dynamic_cast<BooleanActions*>(action); 
		if (jumpAction && jumpAction->GetName() == "jump") {
			std::cout << "Started!\n"; 
		}
	}
}

void SpaceInvaderPlayer::OnActionTriggered(InputActions* action)
{
	if (action->GetType() == ActionType::Boolean) {
		auto* jumpAction = dynamic_cast<BooleanActions*>(action);
		if (jumpAction && jumpAction->GetName() == "shoot") {
			std::cout << "Triggered!\n";
		}
	}
}

void SpaceInvaderPlayer::OnActionEnded(InputActions* action)
{
	if (action->GetType() == ActionType::Boolean) {
		auto* jumpAction = dynamic_cast<BooleanActions*>(action);
		if (jumpAction) {
			std::cout << "Ended!\n";
		}
	}
}
