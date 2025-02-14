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
	inputManager.CreateNewBooleanBinding(SDLK_SPACE, this);
}

void SpaceInvaderPlayer::Update()
{
	Actor::Update();
}

void SpaceInvaderPlayer::Destroy()
{
	Actor::Destroy();
}

void SpaceInvaderPlayer::OnActionTriggered(InputActions* action)
{
	if (action->GetType() == ActionType::Boolean) {
		auto* jumpAction = dynamic_cast<BooleanActions*>(action);
		if (jumpAction && jumpAction->GetState()) {
			std::cout << "Player is jumping!\n";
		}
	}
}
