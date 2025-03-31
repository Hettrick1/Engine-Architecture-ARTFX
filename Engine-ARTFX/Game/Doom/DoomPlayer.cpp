#include "DoomPlayer.h"
#include "DoomPC.h"
#include "CameraComponent.h"
#include "RigidbodyComponent.h"
#include "SpriteComponent.h"
#include "Assets.h"
#include "Scene.h"
#include "MeshComponent.h"

DoomPlayer::DoomPlayer()
	: Actor()
{
}

DoomPlayer::~DoomPlayer()
{
}

void DoomPlayer::Start()
{
	Actor::Start();
	RigidbodyComponent* rigidBody = new RigidbodyComponent(this);
	SetRigidBody(rigidBody);
	DoomPC* playerController = new DoomPC(this, 1);
	AddComponent(playerController);
	Texture* tex3 = Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/WalkAnim/Walk1.png", "walk1");

	CameraComponent* cameraComponent = new CameraComponent(this);
	cameraComponent->SetRelativePosition(Vector3D(0, 0, 0));
	AddComponent(cameraComponent);
	SpriteComponent* sc = new SpriteComponent(this, *tex3, 1);
	AddComponent(sc);
	sc->SetRelativePosition(Vector3D(0, 10, 0));
	sc->RelativeRotateX(90);

	/*Texture* tex2 = Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/gray.png", "walls");
	Texture* tex = Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/planks.png", "cube");
	Mesh* mesh = Assets::LoadMesh("Imports/Meshes/cube.obj", "cube");
	mesh->AddTexture(tex2);
	MeshComponent* meshComp = new MeshComponent(this, mesh);
	meshComp->SetTextureIndex(0);
	AddComponent(meshComp);*/
}

void DoomPlayer::Update()
{
	Actor::Update();
}

void DoomPlayer::Destroy()
{
}
