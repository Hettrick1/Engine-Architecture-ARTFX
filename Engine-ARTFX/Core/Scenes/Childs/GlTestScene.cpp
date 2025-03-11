#include "GlTestScene.h"
#include "TestOpenGl/testGlPlayer.h"
#include "TestOpenGl/Cube.h"
#include "CameraActor.h"
#include "RigidbodyComponent.h"
#include "MeshComponent.h"

GlTestScene::GlTestScene()
{
}

GlTestScene::~GlTestScene()
{
}

void GlTestScene::Start(IRenderer* renderer)
{
	Scene::Start(renderer);

	testGlPlayer* player = new testGlPlayer();
	AddActor(player);
	player->Start();
	player->SetPosition(Vector3D(300, 0, 0));
	player->GetTransformComponent().SetSize({ 1, 1, 0 });

	Cube* ground = new Cube(); 
	AddActor(ground); 
	ground->SetPosition(Vector3D(0.0f, 35.0f, -8.0f)); 
	ground->GetTransformComponent().SetSize({ 20, 60, 1 }); 
	ground->Start(); 
	ground->GetComponentOfType<RigidbodyComponent>()->SetUseGravity(false); 
	ground->GetComponentOfType<RigidbodyComponent>()->SetMass(10000000); 
	ground->GetComponentOfType<RigidbodyComponent>()->SetIsStatic(true);

	Cube* quille3 = new Cube();
	AddActor(quille3);
	quille3->GetTransformComponent().SetSize(Vector3D(1, 1, 2));
	quille3->SetPosition(Vector3D(1.2f, 34.0f, -2.5f));
	quille3->Start();
	quille3->GetComponentOfType<RigidbodyComponent>()->SetMass(0.5);

	Cube* quille4 = new Cube();
	AddActor(quille4);
	quille4->GetTransformComponent().SetSize(Vector3D(1, 1, 2));
	quille4->SetPosition(Vector3D(-1.2f, 34.0f, -2.5f));
	quille4->Start();
	quille4->GetComponentOfType<RigidbodyComponent>()->SetMass(0.5);

	Cube* quille5 = new Cube();
	AddActor(quille5);
	quille5->GetTransformComponent().SetSize(Vector3D(1, 1, 2));
	quille5->SetPosition(Vector3D(0.0f, 34.0f, -2.5f));
	quille5->Start();
	quille5->GetComponentOfType<RigidbodyComponent>()->SetMass(0.5);

	Cube* quille = new Cube();
	AddActor(quille);
	quille->GetTransformComponent().SetSize(Vector3D(1, 1, 2));
	quille->SetPosition(Vector3D(0.6f, 32.0f, -2.5f));
	quille->Start();
	quille->GetComponentOfType<RigidbodyComponent>()->SetMass(0.5);
	//quille->GetComponentOfType<RigidbodyComponent>()->SetIsGrounded(true);

	Cube* quille1 = new Cube();
	AddActor(quille1);
	quille1->GetTransformComponent().SetSize(Vector3D(1, 1, 2));
	quille1->SetPosition(Vector3D(-0.6f, 32.0f, -2.5f));
	quille1->Start();
	quille1->GetComponentOfType<RigidbodyComponent>()->SetMass(0.5);
	//quille1->GetComponentOfType<RigidbodyComponent>()->SetIsGrounded(true);

	Cube* quille2 = new Cube();
	AddActor(quille2);
	quille2->GetTransformComponent().SetSize(Vector3D(1, 1, 2));
	quille2->SetPosition(Vector3D(0.0f, 30.0f, -2.5f));
	quille2->Start();
	quille2->GetComponentOfType<RigidbodyComponent>()->SetMass(0.5);

	Cube* ball = new Cube();
	AddActor(ball);
	ball->Start();
	ball->SetPosition(Vector3D(0.0f, 2.0f, -3.0f));
	ball->GetComponentOfType<MeshComponent>()->SetTextureIndex(1);
	ball->GetComponentOfType<RigidbodyComponent>()->SetMass(5);
	ball->GetComponentOfType<RigidbodyComponent>()->AddImpulse(Vector3D(0, 120, 0));

	CameraActor* camera = new CameraActor();
	camera->Start();
	AddActor(camera);
}

void GlTestScene::Update()
{
	Scene::Update();
}

void GlTestScene::Render()
{
	Scene::Render();
}

void GlTestScene::Close()
{
}
