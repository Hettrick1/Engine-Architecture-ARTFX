#include "GlTestScene.h"
#include "TestOpenGl/testGlPlayer.h"

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
	mRenderer->SetCurrentShaderProgram(mShaderProgram);

	testGlPlayer* player = new testGlPlayer();
	AddActor(player);
	player->Start();
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
