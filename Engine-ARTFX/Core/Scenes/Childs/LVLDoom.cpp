#include "LVLDoom.h"
#include "Doom/DoomPlayer.h"
#include "Doom/DoomPC.h"
#include "TestOpenGl/Cube.h"
#include "CameraActor.h"
#include "MeshComponent.h"
#include "Doom/AmoPickup.h"
#include "Doom/HealthPickUp.h"
#include "Doom/ShieldPickUp.h"
#include "CoreActors/BasicCube.h"
#include "CoreActors/SkySphere.h"
#include "Doom/DoomEnemy.h"
#include "Planets/Planet.h"

LVLDoom::LVLDoom()
	: mPlayer(nullptr)
{
}

LVLDoom::~LVLDoom()
{
	if (mPlayer != nullptr)
	{
		delete mPlayer;
		mPlayer = nullptr;
	}
}

void LVLDoom::Start(IRenderer* renderer)
{
	Scene::Start(renderer);
	mPlayer = new DoomPlayer();
	AddActor(mPlayer);
	mPlayer->Start();

	/*SkySphere* skySphere = new SkySphere(false, {
		"Imports/Sprites/Doom/skybox/bottom.png",
		"Imports/Sprites/Doom/skybox/top.png",
		"Imports/Sprites/Doom/skybox/back.png",
		"Imports/Sprites/Doom/skybox/left.png",
		"Imports/Sprites/Doom/skybox/front.png",
		"Imports/Sprites/Doom/skybox/right.png",
		});
	skySphere->Start();
	AddActor(skySphere);*/

	Shader vert, frag, tcs, tes = Shader();

	vert.Load("VertFrag/PlanetsNoise.vert", ShaderType::VERTEX);
	frag.Load("VertFrag/PlanetsNoise.frag", ShaderType::FRAGMENT);
	tcs.Load("Tesselation/PlanetsNoise.tesc", ShaderType::TESSELLATION_CONTROL);
	tes.Load("Tesselation/PlanetsNoise.tese", ShaderType::TESSELLATION_EVALUATION);

	ShaderProgram* shaderProg5 = new ShaderProgram();
	shaderProg5->Compose({ &vert, &tcs, &tes, &frag });

	CubeTextureMap* cubemap = new CubeTextureMap();
	cubemap->CreateCubeTextureMap({
		"Imports/Sprites/Doom/skybox/bottom.png",
		"Imports/Sprites/Doom/skybox/back.png",
		"Imports/Sprites/Doom/skybox/front.png",
		"Imports/Sprites/Doom/skybox/top.png",
		"Imports/Sprites/Doom/skybox/left.png",
		"Imports/Sprites/Doom/skybox/right.png",
		});

	Planet* planet4 = new Planet(Vector3D(-18, 10, 0), 1, Quaternion(0, 0, 0, 1), shaderProg5, cubemap);
	AddActor(planet4);
	planet4->Start();

	Cube* cube = new Cube(Vector3D(3,3,0), 1);
	AddActor(cube);
	cube->Start();
	cube->GetComponentOfType<MeshComponent>()->SetTiling(Vector2D(10, 10));
	cube->SetTag("Wall");
	cube->GetRigidBody()->SetIsStatic(true);

	Cube* cube2 = new Cube(Vector3D(5, 5, -1.2), Vector3D(100,100,0.1));
	AddActor(cube2);
	cube2->Start();
	cube2->RemoveComponent(cube2->GetRigidBody());
	cube2->GetComponentOfType<MeshComponent>()->SetTextureIndex(2);
	cube2->GetComponentOfType<MeshComponent>()->SetTiling(Vector2D(600, 600));
	cube2->SetTag("Wall");

	AmoPickup* amoPu = new AmoPickup(Vector3D(10, 10, -0.5));
	AddActor(amoPu);
	amoPu->Start();
	HealthPickUp* HealthPu = new HealthPickUp(Vector3D(20, 10, -0.5));
	AddActor(HealthPu);
	HealthPu->Start();
	ShieldPickUp* shieldPu = new ShieldPickUp(Vector3D(30, 10, -0.5));
	AddActor(shieldPu);
	shieldPu->Start();

	DoomEnemy* enemy = new DoomEnemy(mPlayer, Vector3D(10, 20, -0.1));
	AddActor(enemy);
	enemy->Start();
}

void LVLDoom::Update()
{
	Scene::Update();
}

void LVLDoom::Render()
{
	Scene::Render();
}

void LVLDoom::Close()
{
	Scene::Close();
}
