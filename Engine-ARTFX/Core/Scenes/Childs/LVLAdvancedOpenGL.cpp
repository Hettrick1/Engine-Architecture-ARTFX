#include "LVLAdvancedOpenGL.h"
#include "CoreActors/BasicCube.h"
#include "Shaders/Shader.h"
#include "Shaders/ShaderProgram.h"
#include "Doom/DoomPlayer.h"

LVLAdvancedOpenGl::LVLAdvancedOpenGl()
	: Scene()
{
}

LVLAdvancedOpenGl::~LVLAdvancedOpenGl()
{
}

void LVLAdvancedOpenGl::Start(IRenderer* renderer)
{
	Scene::Start(renderer);
	Shader vert = Shader();
	vert.Load("BasicMesh.vert", ShaderType::VERTEX);
	Shader frag = Shader();
	frag.Load("BasicMesh.frag", ShaderType::FRAGMENT);
	Shader tcs = Shader();
	tcs.Load("BasicMesh.tcs", ShaderType::TESSELLATION_CONTROL);
	Shader tes = Shader();
	tes.Load("BasicMesh.tes", ShaderType::TESSELLATION_EVALUATION);

	Scene::ActiveScene->GetRenderer()->GetDebugRenderer()->SetDrawDebug(false);

	ShaderProgram* shaderProg = new ShaderProgram();
	shaderProg->Compose({ &vert, &frag, &tcs, &tes });
	BasicCube* cube = new BasicCube(0, 10, Quaternion(0,0,0,1), shaderProg);
	AddActor(cube);
	cube->Start();
	DoomPlayer* player = new DoomPlayer();
	AddActor(player);
	player->Start();
}

void LVLAdvancedOpenGl::Update()
{
	Scene::Update();
}

void LVLAdvancedOpenGl::Render()
{
	Scene::Render();
}

void LVLAdvancedOpenGl::Close()
{
	Scene::Close();
}
