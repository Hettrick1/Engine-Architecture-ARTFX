#include "LVLAdvancedOpenGL.h"
#include "CoreActors/BasicCube.h"
#include "Shaders/Shader.h"
#include "Shaders/ShaderProgram.h"
#include "Doom/DoomPlayer.h"
#include "TestOpenGl/Cube.h"

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
	vert.Load("VertFrag/Advanced.vert", ShaderType::VERTEX);
	Shader frag = Shader();
	frag.Load("VertFrag/Advanced.frag", ShaderType::FRAGMENT);
	Shader tcs = Shader();
	tcs.Load("Tesselation/Advanced.tesc", ShaderType::TESSELLATION_CONTROL);
	Shader tes = Shader();
	tes.Load("Tesselation/Advanced.tese", ShaderType::TESSELLATION_EVALUATION);

	Scene::ActiveScene->GetRenderer()->GetDebugRenderer()->SetDrawBoxes(false);

	ShaderProgram* shaderProg = new ShaderProgram();
	shaderProg->Compose({ &vert, &tcs, &tes, &frag });
	BasicCube* cube = new BasicCube(Vector3D(-2, 0, -1), 3, Quaternion(0, 0, 0, 1), shaderProg);
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
