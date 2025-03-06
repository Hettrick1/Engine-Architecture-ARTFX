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

	Cube* cube = new Cube();
	AddActor(cube);
	cube->SetPosition(Vector3D(-3.0f, 10.0f, 3.0f));
	cube->Start();
	cube->GetComponentOfType<RigidbodyComponent>()->AddImpulse(Vector3D(5, 0, 0));

	Cube* cube3 = new Cube();
	AddActor(cube3);
	cube3->Start();
	cube3->SetPosition(Vector3D(3.0f, 10.0f, 3.0f));
	cube3->GetComponentOfType<MeshComponent>()->SetTextureIndex(1);
	cube3->GetComponentOfType<RigidbodyComponent>()->SetMass(1);
	cube3->GetComponentOfType<RigidbodyComponent>()->SetMass(1.5);
	cube3->GetComponentOfType<RigidbodyComponent>()->AddImpulse(Vector3D(-13, 0, 0));


	Cube* cube2 = new Cube();
	AddActor(cube2);
	cube2->SetPosition(Vector3D(0.0f, 5.0f, -4.0f));
	cube2->GetTransformComponent().SetSize({ 20, 20, 1 });
	cube2->Start();
	cube2->GetComponentOfType<RigidbodyComponent>()->SetUseGravity(false);
	cube2->GetComponentOfType<RigidbodyComponent>()->SetMass(10000000);

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
