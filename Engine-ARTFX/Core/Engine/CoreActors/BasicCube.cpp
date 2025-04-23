#include "BasicCube.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "Scene.h"
#include "Timer.h"
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
	Texture* tex1 = Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/Doom/268.png", "wallTex");
	Texture* tex2 = Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/Doom/091.png", "groundTex");
	Texture* tex3 = Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/Doom/268bis.png", "wallTex2");
	Texture* tex4 = Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/uv_mapper.jpg", "uvMapper");
	Mesh* mesh = Assets::LoadMesh("Imports/Meshes/cube.obj", "cube");
	mesh->AddTexture(tex1);
	mesh->AddTexture(tex2); 
	mesh->AddTexture(tex3); 
	mesh->AddTexture(tex4);
	MeshComponent* meshComp = new MeshComponent(this, mesh, mShaderProgram);
	meshComp->SetTextureIndex(1);
	BoxCollider3DComponent* bc = new BoxCollider3DComponent(this, 10, GetTransformComponent().GetSize());
}

void BasicCube::Update()
{
	Actor::Update();
	mTransformComponent.RotateZ(Timer::deltaTime * 50);
	mTransformComponent.RotateX(Timer::deltaTime * 50);
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
