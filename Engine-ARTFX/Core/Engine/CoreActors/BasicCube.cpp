#include "BasicCube.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "Scene.h"
#include "BoxCollider3DComponent.h"

BasicCube::BasicCube(Vector3D pPos, Vector3D pSize, Quaternion pRotation, ShaderProgram* program)
	: Actor(pPos, pSize, pRotation), mShaderProgram(program)
{
}

BasicCube::~BasicCube()
{
}

void BasicCube::Start()
{
	Actor::Start();
	Texture* tex = Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/day.png", "LakeSkyTexture");
	Mesh* mesh = Assets::LoadMesh("Imports/Meshes/cube.obj", "cube");
	mesh->AddTexture(tex);
	MeshComponent* meshComp = new MeshComponent(this, mesh, mShaderProgram);
	meshComp->SetTextureIndex(1);
	BoxCollider3DComponent* bc = new BoxCollider3DComponent(this, 10, GetTransformComponent().GetSize());
}

void BasicCube::Update()
{
	Actor::Update();
}

void BasicCube::Destroy()
{
	Actor::Destroy();
}

void BasicCube::OnTriggerEnter(ColliderComponent* collider, HitResult* infos)
{
}

void BasicCube::OnTriggerStay(ColliderComponent* collider, HitResult* infos)
{
}

void BasicCube::OnTriggerExit(ColliderComponent* collider, HitResult* infos)
{
}
