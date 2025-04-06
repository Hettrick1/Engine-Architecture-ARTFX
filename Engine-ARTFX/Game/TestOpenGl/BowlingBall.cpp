#include "BowlingBall.h"
#include "Scene.h"
#include "MeshComponent.h"
#include "RigidbodyComponent.h"
#include "Timer.h"
#include "Physics/CollisionManager.h"
#include "BoxCollider3DComponent.h"

BowlingBall::BowlingBall(Vector3D pPos, Vector3D pSize, Quaternion pRotation)
	: Actor(pPos, pSize, pRotation)
{
}

BowlingBall::~BowlingBall()
{
}

void BowlingBall::Start()
{
	Actor::Start();
	Texture* tex = Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/ball.jpg", "sphere");
	Mesh* mesh = Assets::LoadMesh("Imports/Meshes/sphere.obj", "sphere");
	mesh->AddTexture(tex);
	MeshComponent* meshComp = new MeshComponent(this, mesh);
	meshComp->SetTextureIndex(1);
	AddComponent(meshComp);
	RigidbodyComponent* rb = new RigidbodyComponent(this);
	AddComponent(rb);
	BoxCollider3DComponent* bc = new BoxCollider3DComponent(this, 10, GetTransformComponent().GetSize());
	AddComponent(bc);
}

void BowlingBall::Update()
{
	Actor::Update();
	if (GetRigidBody()->GetVelocity().LengthSq() > 0.1) {
		GetTransformComponent().RotateX(-GetRigidBody()->GetVelocity().LengthSq() * 2 * Timer::deltaTime);
	}
}

void BowlingBall::Destroy()
{
	Actor::Destroy();
}

void BowlingBall::OnTriggerEnter(ColliderComponent* collider, HitResult* infos)
{
}

void BowlingBall::OnTriggerStay(ColliderComponent* collider, HitResult* infos)
{
}

void BowlingBall::OnTriggerExit(ColliderComponent* collider, HitResult* infos)
{
}
