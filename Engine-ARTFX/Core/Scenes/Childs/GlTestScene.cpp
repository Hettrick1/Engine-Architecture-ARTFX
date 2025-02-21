#include "GlTestScene.h"

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
	mVertexShader.Load("Simple.frag", ShaderType::FRAGMENT);
	mShaderProgram.Compose({ &mVertexShader, &mFragmentShader });
	mRenderer->SetCurrentShaderProgram(mShaderProgram);
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
