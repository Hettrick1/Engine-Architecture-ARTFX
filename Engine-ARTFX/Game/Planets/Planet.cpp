#include "Planet.h"
#include "CubeMapMeshComponent.h"
#include "Assets.h"
#include "CameraComponent.h"
#include "CameraManager.h"

Planet::Planet(Vector3D pPos, Vector3D pSize, Quaternion pRotation, ShaderProgram* program)
	:Actor(pPos, pSize, pRotation), mShaderProgram(program)
{
}

Planet::~Planet()
{
}

void Planet::Start()
{
	Actor::Start();
	Mesh* mesh = Assets::LoadMesh("Imports/Meshes/cube.obj", "cube");
	Shader vert, frag, tcs, tes = Shader();
	vert.Load("VertFrag/Planets.vert", ShaderType::VERTEX);
	frag.Load("VertFrag/Planets.frag", ShaderType::FRAGMENT);
	tcs.Load("Tesselation/Planets.tesc", ShaderType::TESSELLATION_CONTROL);
	tes.Load("Tesselation/Planets.tese", ShaderType::TESSELLATION_EVALUATION);

	ShaderProgram* shaderProg = new ShaderProgram();
	shaderProg->Compose({ &vert, &tcs, &tes, &frag });

	CubeTextureMap cubemap;
	cubemap.CreateCubeTextureMap({
		"Imports/Sprites/CubeMap/nx.png",
		"Imports/Sprites/CubeMap/px.png",
		"Imports/Sprites/CubeMap/py.png",
		"Imports/Sprites/CubeMap/ny.png",
		"Imports/Sprites/CubeMap/nz.png",
		"Imports/Sprites/CubeMap/pz.png", 
		});

	CubeMapMeshComponent* meshComponent = new CubeMapMeshComponent(this, mesh, cubemap, shaderProg);
}

void Planet::Update()
{
	Actor::Update();
	Vector3D camPos = CameraManager::Instance().GetCurrentCamera()->GetWorldTransform().GetTranslation();
	Vector3D dist = camPos - GetTransformComponent().GetPosition();
	float distSq = dist.LengthSq();

	if (distSq < 800.0f)
		mLod = 16;
	else if (distSq < 1800.0f)
		mLod = 10;
	else if (distSq < 2800.0f)
		mLod = 4;
	else
		mLod = 2;
}

void Planet::Destroy()
{
	Actor::Destroy();
}
