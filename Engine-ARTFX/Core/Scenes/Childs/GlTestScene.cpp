#include "GlTestScene.h"
#include "TestOpenGl/testGlPlayer.h"
#include "TestOpenGl/Cube.h"
#include "CameraActor.h"

GlTestScene::GlTestScene()
{
}

GlTestScene::~GlTestScene()
{
}

void GlTestScene::Start(IRenderer* renderer)
{
	Scene::Start(renderer);
	mVertexShader.Load("Simple.vert", ShaderType::VERTEX);
	mFragmentShader.Load("Simple.frag", ShaderType::FRAGMENT);
	mShaderProgram.Compose({ &mVertexShader, &mFragmentShader });
	mRenderer->SetSpriteShaderProgram(mShaderProgram);

	testGlPlayer* player = new testGlPlayer();
	AddActor(player);
	player->Start();
	player->SetPosition(Vector3D(200, 0, 0));
	player->GetTransformComponent().SetSize({ 1, 1, 0 });
	Cube* cube = new Cube();
	AddActor(cube);
	cube->SetPosition(Vector3D(1.0f, 0.0f, 0.0f));
	cube->Start();
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
