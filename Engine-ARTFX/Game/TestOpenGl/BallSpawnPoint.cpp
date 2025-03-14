#include "BallSpawnPoint.h"

#include "Scene.h"
#include "MeshComponent.h"

BallSpawnPoint::BallSpawnPoint(Vector3D pPos, Vector3D pSize, Quaternion pRotation)
	: Actor(pPos, pSize, pRotation)
{
}

BallSpawnPoint::~BallSpawnPoint()
{
}

void BallSpawnPoint::Start()
{
	Actor::Start();
	Texture* tex = Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/gray.png", "walls");
	Mesh* mesh = Assets::LoadMesh("Imports/Meshes/cube.obj", "cube");
	mesh->AddTexture(tex);
	MeshComponent* meshComp = new MeshComponent(this, mesh);
	meshComp->SetTextureIndex(1);
	AddComponent(meshComp);
}

void BallSpawnPoint::Update()
{
	Actor::Update();
}

void BallSpawnPoint::Destroy()
{
	Actor::Destroy();
}
