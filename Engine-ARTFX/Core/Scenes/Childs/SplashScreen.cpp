#include "SplashScreen.h"

#include "CameraActor.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "HudElement.h"
#include "Timer.h"
#include "TextRenderer.h"
#include "HudManager.h" 

SplashScreen::SplashScreen()
	: Scene(), mZephyrusText(nullptr), mStudioText(nullptr), mTime(0)
{
}

SplashScreen::~SplashScreen()
{
	delete mZephyrusText;
	delete mStudioText;
}

void SplashScreen::Start(IRenderer* renderer)
{
	Scene::Start(renderer);

	mTime = 0;

	CameraActor* cam = new CameraActor();
	cam->Start();
	AddActor(cam);

	mZephyrusText = new HudText("Zephyrus", 0, 0, 2.0f, Vector4D(1.0, 0.81176f, 0.0, 0), TextAlignment::CENTER, Assets::LoadFont("Imports/Fonts/Chopsic.otf", "RoadPixel"));
	GetRenderer()->GetHud()->AddElement(mZephyrusText);

	Shader vert;
	vert.Load("VertFrag/TextSplashScreen.vert", ShaderType::VERTEX);
	Shader frag;
	frag.Load("VertFrag/TextSplashScreen.frag", ShaderType::FRAGMENT);
	ShaderProgram* shaderProgram = new ShaderProgram();
	shaderProgram->Compose({ &vert, &frag });
	mZephyrusText->SetShaderProgram(shaderProgram);

	mStudioText = new HudText("Engine", 0, -200, 0.5f, Vector4D(1, 1, 1, 0), TextAlignment::CENTER, Assets::LoadFont("Imports/Fonts/Chopsic.otf", "RoadPixel"));
	GetRenderer()->GetHud()->AddElement(mStudioText);
}

void SplashScreen::Update()
{
	Scene::Update();
	mTime += Timer::deltaTime;
	if (mTime > 0.2f && mTime < 0.7)
	{
		float alpha = (mTime - 0.2f) * 2;
		mZephyrusText->SetColor(Vector4D(mZephyrusText->GetColor().xyz, alpha));
	}
	if (mTime > 2.1f && mTime < 2.6)
	{
		float alpha = (mTime - 2.1f) * 2;
		mStudioText->SetColor(Vector4D(mStudioText->GetColor().xyz, alpha));
	}
	if (mTime > 3.0f)
	{
		Scene::ActiveScene->Close();
	}
}

void SplashScreen::Render()
{
	Scene::Render();
}

void SplashScreen::Close()
{
	Scene::Close();
}
