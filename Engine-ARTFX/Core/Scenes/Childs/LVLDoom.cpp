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
	mPlayer->SetPosition(Vector3D(-48, 0, 0));
	mPlayer->RotateZ(-90);

	SkySphere* skySphere = new SkySphere(false, {
		"Imports/Sprites/Doom/skybox/front.png",
		"Imports/Sprites/Doom/skybox/back.png",
		"Imports/Sprites/Doom/skybox/top.png",
		"Imports/Sprites/Doom/skybox/bottom.png",
		"Imports/Sprites/Doom/skybox/left.png",
		"Imports/Sprites/Doom/skybox/right.png",
		});
	skySphere->Start();
	AddActor(skySphere);

	Shader vert, frag, tcs, tes = Shader();

	vert.Load("VertFrag/PlanetsNoise.vert", ShaderType::VERTEX);
	frag.Load("VertFrag/PlanetsNoise.frag", ShaderType::FRAGMENT);
	tcs.Load("Tesselation/PlanetsNoise.tesc", ShaderType::TESSELLATION_CONTROL);
	tes.Load("Tesselation/PlanetsNoise.tese", ShaderType::TESSELLATION_EVALUATION);

	ShaderProgram* shaderProg5 = new ShaderProgram();
	shaderProg5->Compose({ &vert, &tcs, &tes, &frag });

	BasicCube* wall = new BasicCube(Vector3D(0, 50, -0.21), Vector3D(50, 1, 1));
	AddActor(wall);
	wall->Start();
	wall->RotateX(90);
	wall->GetComponentOfType<MeshComponent>()->SetTextureIndex(3);
	wall->GetComponentOfType<MeshComponent>()->SetTiling(Vector2D(150, 6));
	wall->SetTag("Wall");

	BasicCube* wall1 = new BasicCube(Vector3D(0, -50, -0.21), Vector3D(50, 1, 1));
	AddActor(wall1);
	wall1->Start();
	wall1->RotateX(90);
	wall1->GetComponentOfType<MeshComponent>()->SetTextureIndex(3);
	wall1->GetComponentOfType<MeshComponent>()->SetTiling(Vector2D(150, 6));
	wall1->SetTag("Wall");

	BasicCube* wall2 = new BasicCube(Vector3D(50, 0, -0.21), Vector3D(1, 50, 1));
	AddActor(wall2);
	wall2->Start();
	wall2->RotateY(90);
	wall2->GetComponentOfType<MeshComponent>()->SetTiling(Vector2D(6, 150));
	wall2->SetTag("Wall");

	BasicCube* wall3 = new BasicCube(Vector3D(-50, 0, -0.21), Vector3D(1, 50, 1));
	AddActor(wall3);
	wall3->Start();
	wall3->RotateY(90);
	wall3->GetComponentOfType<MeshComponent>()->SetTiling(Vector2D(6, 150));
	wall3->SetTag("Wall");

	BasicCube* wall4 = new BasicCube(Vector3D(0, -30, -0.21), Vector3D(1, 20, 1));
	AddActor(wall4);
	wall4->Start();
	wall4->RotateY(90);
	wall4->GetComponentOfType<MeshComponent>()->SetTiling(Vector2D(6, 150));
	wall4->SetTag("Wall");

	BasicCube* wall5 = new BasicCube(Vector3D(0, 30, -0.21), Vector3D(1, 20, 1));
	AddActor(wall5);
	wall5->Start();
	wall5->RotateY(90);
	wall5->GetComponentOfType<MeshComponent>()->SetTiling(Vector2D(6, 150));
	wall5->SetTag("Wall");

	BasicCube* wall6 = new BasicCube(Vector3D(0, -9, -0.21), Vector3D(1, 1, 1));
	AddActor(wall6);
	wall6->Start();
	wall6->RotateY(90);
	wall6->GetComponentOfType<MeshComponent>()->SetTiling(Vector2D(6, 6));
	wall6->SetTag("Wall");

	BasicCube* wall7 = new BasicCube(Vector3D(0, 9, -0.21), Vector3D(1, 1, 1));
	AddActor(wall7);
	wall7->Start();
	wall7->RotateY(90);
	wall7->GetComponentOfType<MeshComponent>()->SetTiling(Vector2D(6, 6));
	wall7->SetTag("Wall");

	BasicCube* wall8 = new BasicCube(Vector3D(0, 9, -0.21), Vector3D(1, 1, 1));
	AddActor(wall8);
	wall8->Start();
	wall8->RotateY(90);
	wall8->GetComponentOfType<MeshComponent>()->SetTiling(Vector2D(6, 6));
	wall8->SetTag("Wall");

	BasicCube* wall9 = new BasicCube(Vector3D(-30, 0, -0.21), Vector3D(1, 1, 1));
	AddActor(wall9);
	wall9->Start();
	wall9->RotateY(0);
	wall9->GetComponentOfType<MeshComponent>()->SetTiling(Vector2D(6, 6));
	wall9->SetTag("Wall");

	BasicCube* wall10 = new BasicCube(Vector3D(-48, -10, -0.21), Vector3D(1, 1, 1));
	AddActor(wall10);
	wall10->Start();
	wall10->RotateY(0);
	wall10->GetComponentOfType<MeshComponent>()->SetTiling(Vector2D(6, 6));
	wall10->SetTag("Wall");

	BasicCube* wall11 = new BasicCube(Vector3D(-48, 10, -0.21), Vector3D(1, 1, 1));
	AddActor(wall11);
	wall11->Start();
	wall11->RotateY(0);
	wall11->GetComponentOfType<MeshComponent>()->SetTiling(Vector2D(6, 6));
	wall11->SetTag("Wall");

	BasicCube* cube2 = new BasicCube(Vector3D(0, 0, -1.2), Vector3D(50,50,0.1));
	AddActor(cube2);
	cube2->Start();
	cube2->GetComponentOfType<MeshComponent>()->SetTextureIndex(2);
	cube2->GetComponentOfType<MeshComponent>()->SetTiling(Vector2D(300, 300));
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
