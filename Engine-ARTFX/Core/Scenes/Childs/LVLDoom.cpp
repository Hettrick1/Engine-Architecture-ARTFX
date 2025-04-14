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
#include "Doom/DoomEnemy.h"

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
	cube2->GetComponentOfType<MeshComponent>()->SetTiling(Vector2D(100, 100));
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
