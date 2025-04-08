#include "BowlingOpenGl.h"
#include "TestOpenGl/testGlPlayer.h"
#include "TestOpenGl/Cube.h"
#include "TestOpenGl/BowlingBall.h"
#include "TestOpenGl/BowlingPin.h"
#include "CameraActor.h"
#include "TestOpenGl/BowlingPlayer.h"
#include "RigidbodyComponent.h"
#include "BoxCollider3DComponent.h"
#include "MeshComponent.h"
#include "CoreActors/BasicCube.h"

BowlingOpenGl::BowlingOpenGl()
	: mBowlingPlayer(nullptr)
{
}

BowlingOpenGl::~BowlingOpenGl()
{
}

void BowlingOpenGl::Start(IRenderer* renderer)
{
	Scene::Start(renderer);

	testGlPlayer* player = new testGlPlayer();
	AddActor(player);
	player->Start();
	player->SetPosition(Vector3D(300, 0, 0));

	BasicCube* ground = new BasicCube();
	AddActor(ground); 
	ground->SetPosition(Vector3D(0.0, 35.0f, -6.0f)); 
	ground->GetTransformComponent().SetSize({ 15, 60, 1 }); 
	ground->Start();
	ground->GetComponentOfType<MeshComponent>()->SetTiling(Vector2D(2, 1));

	BowlingPin* quille3 = new BowlingPin();
	AddActor(quille3);
	quille3->GetTransformComponent().SetSize(0.8f);
	quille3->SetPosition(Vector3D(3.0f, 36.0f, -4.0f));
	quille3->Start();
	quille3->GetComponentOfType<RigidbodyComponent>()->SetMass(0.5);

	BowlingPin* quille4 = new BowlingPin();
	AddActor(quille4);
	quille4->GetTransformComponent().SetSize(0.8f);
	quille4->SetPosition(Vector3D(-3.0f, 36.0f, -4.0f));
	quille4->Start();
	quille4->GetComponentOfType<RigidbodyComponent>()->SetMass(0.5);

	BowlingPin* quille5 = new BowlingPin();
	AddActor(quille5);
	quille5->GetTransformComponent().SetSize(0.8f);
	quille5->SetPosition(Vector3D(0.0f, 36.0f, -4.0f));
	quille5->Start();
	quille5->GetComponentOfType<RigidbodyComponent>()->SetMass(0.5);

	BowlingPin* quille = new BowlingPin();
	AddActor(quille);
	quille->GetTransformComponent().SetSize(0.8f);
	quille->SetPosition(Vector3D(1.5f, 33.0f, -4.0f));
	quille->Start();
	quille->GetComponentOfType<RigidbodyComponent>()->SetMass(0.5);

	BowlingPin* quille1 = new BowlingPin();
	AddActor(quille1);
	quille1->GetTransformComponent().SetSize(0.8f);
	quille1->SetPosition(Vector3D(-1.5f, 33.0f, -4.0f));
	quille1->Start();
	quille1->GetComponentOfType<RigidbodyComponent>()->SetMass(0.5);

	BowlingPin* quille2 = new BowlingPin();
	AddActor(quille2);
	quille2->GetTransformComponent().SetSize(0.8f);
	quille2->SetPosition(Vector3D(0.0f, 30.0f, -4.0f));
	quille2->Start();
	quille2->GetComponentOfType<RigidbodyComponent>()->SetMass(0.5);

	BasicCube* wall = new BasicCube();
	AddActor(wall);
	wall->SetPosition(Vector3D(15.0f, 35.0f, 0.0f));
	wall->GetTransformComponent().SetSize({ 1, 60, 15 });
	wall->Start();
	wall->GetComponentOfType<MeshComponent>()->SetTextureIndex(3);

	BasicCube* wall1 = new BasicCube();
	AddActor(wall1);
	wall1->SetPosition(Vector3D(-15.0f, 35.0f, 0.0f));
	wall1->GetTransformComponent().SetSize({ 1, 60, 15 });
	wall1->Start();
	wall1->GetComponentOfType<MeshComponent>()->SetTextureIndex(3);

	BasicCube* wall2 = new BasicCube();
	AddActor(wall2);
	wall2->SetPosition(Vector3D(0.0f, 90.0f, 0.0f));
	wall2->GetTransformComponent().SetSize({ 15, 1, 15 });
	wall2->Start();
	wall2->GetComponentOfType<MeshComponent>()->SetTextureIndex(3);

	CameraActor* camera = new CameraActor();
	camera->SetPosition(Vector3D(0.0f, 34.0f, 40.0f));
	camera->GetTransformComponent().RotateX(-90);
	AddActor(camera);
	camera->Start();

	mBowlingPlayer = new BowlingPlayer();
	mBowlingPlayer->GetTransformComponent().RotateX(-5);
	mBowlingPlayer->SetPosition(Vector3D(0.0f, -40.0f, 5.0f));
	AddActor(mBowlingPlayer);
	mBowlingPlayer->Start();

}

void BowlingOpenGl::Update()
{
	Scene::Update();
}

void BowlingOpenGl::Render()
{
	Scene::Render();
}

void BowlingOpenGl::Close()
{
}
