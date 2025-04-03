#include "LVLDoom.h"
#include "Doom/DoomPlayer.h"
#include "Doom/DoomPC.h"
#include "TestOpenGl/Cube.h"
#include "CameraActor.h"
#include "MeshComponent.h"
#include "Doom/AmoPickup.h"

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
	cube->GetComponentOfType<MeshComponent>()->GetMesh()->SetTextureTiling(Vector2D(3, 2));
	cube->SetTag("Wall");
	cube->GetRigidBody()->SetIsStatic(true);
	Cube* cube2 = new Cube(Vector3D(5, 5, -1.2), Vector3D(10,10,0.1));
	AddActor(cube2);
	cube2->Start();
	cube2->GetRigidBody()->SetIsStatic(true);
	cube2->GetComponentOfType<MeshComponent>()->GetMesh()->SetTextureTiling(Vector2D(3, 2));
	cube2->SetTag("Wall");
	AmoPickup* amoPu = new AmoPickup(Vector3D(10, 10, -0.5));
	AddActor(amoPu);
	amoPu->Start();
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
