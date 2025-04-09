#include "LVLAdvancedOpenGL.h"
#include "CoreActors/BasicCube.h"
#include "Shaders/Shader.h"
#include "Shaders/ShaderProgram.h"
#include "Doom/DoomPlayer.h"
#include "TestOpenGl/Cube.h"
#include "MeshComponent.h"
#include "TestOpenGl/Sphere.h"
#include "CoreActors/SkySphere.h"

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
	SkySphere* skySphere = new SkySphere();
	skySphere->Start();
	AddActor(skySphere);
	Scene::ActiveScene->GetRenderer()->GetDebugRenderer()->SetDrawBoxes(false);

	Shader vert, frag, tcs, tes = Shader();
	vert.Load("VertFrag/Advanced.vert", ShaderType::VERTEX);
	frag.Load("VertFrag/Advanced.frag", ShaderType::FRAGMENT);
	tcs.Load("Tesselation/Advanced.tesc", ShaderType::TESSELLATION_CONTROL);
	tes.Load("Tesselation/Advanced.tese", ShaderType::TESSELLATION_EVALUATION);

	ShaderProgram* shaderProg = new ShaderProgram();
	shaderProg->Compose({ &vert, &tcs, &tes, &frag });

	BasicCube* cube = new BasicCube(Vector3D(-3, 0, -1), 3, Quaternion(0, 0, 0, 1), shaderProg);
	AddActor(cube);
	cube->Start();

	Sphere* sphere = new Sphere(Vector3D(20, 0, -1), 3, Quaternion(0, 0, 0, 1)); 
	sphere->Start();
	//sphere->GetComponentOfType<MeshComponent>()->SetShaderProgram(*shaderProg); 

	vert.Load("VertFrag/CubeToSphere.vert", ShaderType::VERTEX);
	frag.Load("VertFrag/CubeToSphere.frag", ShaderType::FRAGMENT);
	tcs.Load("Tesselation/CubeToSphere.tesc", ShaderType::TESSELLATION_CONTROL);
	tes.Load("Tesselation/CubeToSphere.tese", ShaderType::TESSELLATION_EVALUATION);

	ShaderProgram* shaderProg2 = new ShaderProgram();
	shaderProg2->Compose({ &vert, &tcs, &tes, &frag });

	BasicCube* cube2 = new BasicCube(Vector3D(8, 0, -1), 3, Quaternion(0, 0, 0, 1), shaderProg2);
	AddActor(cube2);
	cube2->Start();

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
