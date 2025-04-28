#include "BowlingPin.h"
#include "Scene.h"
#include "MeshComponent.h"
#include "RigidbodyComponent.h"
#include "Timer.h"
#include "Physics/CollisionManager.h"
#include "BoxCollider3DComponent.h"

BowlingPin::BowlingPin(Vector3D pPos, Vector3D pSize, Quaternion pRotation)
	: Actor(pPos, pSize, pRotation)
{
}

BowlingPin::~BowlingPin()
{
}

void BowlingPin::Start()
{
	Actor::Start();
	Texture* tex = Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/pin.jpg", "pinTex");
	Mesh* mesh = Assets::LoadMesh("Imports/Meshes/pin.obj", "pin");
	mesh->AddTexture(tex);
	MeshComponent* meshComp = new MeshComponent(this, mesh);
	meshComp->SetTextureIndex(2);
	RigidbodyComponent* rb = new RigidbodyComponent(this);
	BoxCollider3DComponent* bc = new BoxCollider3DComponent(this, 10, Vector3D(GetTransformComponent().GetSize().x, GetTransformComponent().GetSize().y, 2), Vector3D(0,0,2.0));
}

void BowlingPin::Update()
{
	Actor::Update();
}

void BowlingPin::Destroy()
{
	Actor::Destroy();
}

void BowlingPin::OnTriggerEnter(ColliderComponent* collider, HitResult* infos)
{
}

void BowlingPin::OnTriggerStay(ColliderComponent* collider, HitResult* infos)
{
}

void BowlingPin::OnTriggerExit(ColliderComponent* collider, HitResult* infos)
{
}