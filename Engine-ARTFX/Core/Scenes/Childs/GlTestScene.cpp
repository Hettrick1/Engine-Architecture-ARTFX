#include "GlTestScene.h"
#include "TestOpenGl/testGlPlayer.h"
#include "TestOpenGl/Cube.h"
#include "CameraActor.h"
#include "RigidbodyComponent.h"

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
	cube->SetPosition(Vector3D(0.0f, 10.0f, 0.0f));
	cube->Start();

	Cube* cube2 = new Cube();
	AddActor(cube2);
	cube2->SetPosition(Vector3D(0.0f, 5.0f, -3.0f));
	cube2->GetTransformComponent().SetSize({ 20, 20, 1 });
	cube2->Start();
	cube2->GetComponentOfType<RigidbodyComponent>()->SetUseGravity(false);

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
