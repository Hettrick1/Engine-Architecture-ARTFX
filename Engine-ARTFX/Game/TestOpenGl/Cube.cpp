#include "Cube.h"
#include "Scene.h"
#include "MeshComponent.h"
#include "RigidbodyComponent.h"
#include "Timer.h"
#include "Physics/CollisionManager.h"
#include "BoxCollider3DComponent.h"

Cube::Cube(Vector3D pPos, Vector3D pSize, Quaternion pRotation)
	: Actor(pPos, pSize, pRotation)
{
}

Cube::~Cube()
{
}

void Cube::Start()
{
	Actor::Start();
	Texture* tex2 = Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/gray.png", "walls");
	Texture* tex = Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/planks.png", "cube");
	Mesh* mesh = Assets::LoadMesh("Imports/Meshes/cube.obj", "cube");
	mesh->AddTexture(tex2);
	MeshComponent* meshComp = new MeshComponent(this, mesh);
	meshComp->SetTextureIndex(0); 
	RigidbodyComponent* rb = new RigidbodyComponent(this);
	BoxCollider3DComponent* bc = new BoxCollider3DComponent(this, 10, GetTransformComponent().GetSize());
}

void Cube::Update()
{
	Actor::Update();
}

void Cube::Destroy()
{
	Actor::Destroy();
}

void Cube::OnTriggerEnter(ColliderComponent* collider)
{
}

void Cube::OnCollision(ColliderComponent* collider)
{
}

void Cube::OnTriggerStay(ColliderComponent* collider)
{
}

void Cube::OnTriggerExit(ColliderComponent* collider)
{
}
