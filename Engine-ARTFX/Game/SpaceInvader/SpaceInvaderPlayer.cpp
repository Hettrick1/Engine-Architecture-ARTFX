#include "SpaceInvaderPlayer.h"
#include "Scene.h"
#include "BooleanActions.h"
#include "InputManager.h"


SpaceInvaderPlayer::SpaceInvaderPlayer() :
	Actor({ 500, 500 }, 1.0, 0), mWalkAnim(nullptr)
{
}

SpaceInvaderPlayer::~SpaceInvaderPlayer()
{
	delete mWalkAnim;
}

void SpaceInvaderPlayer::Start()
{
	Actor::Start();
	std::vector<Texture*> walkAnimTextures = {
		Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/WalkAnim/Walk1.png", "walk1"),
		Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/WalkAnim/Walk2.png", "walk2"),
		Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/WalkAnim/Walk3.png", "walk3"),
		Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/WalkAnim/Walk4.png", "walk4"),
		Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/WalkAnim/Walk5.png", "walk5")
	};

	mWalkAnim = new FlipbookComponent(this, walkAnimTextures, 500000);
	mWalkAnim->SetAnimationFps(5);

	InputManager& inputManager = InputManager::Instance();
	inputManager.CreateNewBooleanBinding(SDLK_SPACE, this, "jump");
	inputManager.CreateNewBooleanBinding(SDLK_c, this, "shoot");
}

void SpaceInvaderPlayer::Update()
{
	Actor::Update();
	mWalkAnim->Update(); 
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
