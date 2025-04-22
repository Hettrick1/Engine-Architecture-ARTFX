#include "LVLDoomMainMenu.h"
#include "CameraActor.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "HudElement.h"
#include "Timer.h"
#include "TextRenderer.h"
#include "HudManager.h" 
#include "SceneManager.h"
#include "LVLDoom.h"
#include "CoreActors/EmptyActor.h"
#include "Doom/DoomMenuPC.h"

LVLDoomMainMenu::LVLDoomMainMenu()
	: Scene(), mDoomMenu(nullptr), mPressEnter(nullptr), mTimer(0)
{
}

LVLDoomMainMenu::~LVLDoomMainMenu()
{
	delete mDoomMenu;
	delete mPressEnter;
}

void LVLDoomMainMenu::Start(IRenderer* renderer)
{
	Scene::Start(renderer);
	CameraActor* cam = new CameraActor();
	cam->Start();
	AddActor(cam);

	Texture* damageIndicator = Assets::LoadTexture(*GetRenderer(), "Imports/Sprites/Doom/MainMenu.png", "MainMenu");
	mDoomMenu = new HudImage(*damageIndicator, Vector2D(0, 0), 2);
	mDoomMenu->SetTint(Vector4D(1.0, 1.0, 1.0, 1.0));
	GetRenderer()->GetHud()->AddElement(mDoomMenu);

	mPressEnter = new HudText("Press Enter To Begin", 0, -800, 1.0f, Vector4D(1.0, 1.0, 1.0, 0.0), TextAlignment::CENTER);
	GetRenderer()->GetHud()->AddElement(mPressEnter);

	EmptyActor* defaultPawn = new EmptyActor();
	defaultPawn->AddComponent(new DoomMenuPC(defaultPawn, 1));
	defaultPawn->Start();
	AddActor(defaultPawn);
	SDL_SetRelativeMouseMode(SDL_TRUE);
}

void LVLDoomMainMenu::Update()
{
	Scene::Update();
	mTimer += Timer::deltaTime;
	mPressEnter->SetColor(Vector4D(mPressEnter->GetColor().xyz, (Maths::Sin(mTimer * 2) + 1) * 0.5f));
}

void LVLDoomMainMenu::Render()
{
	Scene::Render();
}

void LVLDoomMainMenu::Close()
{
	Scene::Close();
}