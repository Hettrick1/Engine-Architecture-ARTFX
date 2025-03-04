#include "Cube.h"
#include "Scene.h"
#include "MeshComponent.h"
#include "Timer.h"

float rotX = 0;
float rotY = 0;

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
	Texture* tex = Assets::LoadTexture(*GetScene().GetRenderer(), "Imports/Sprites/pokeball.png", "cube");
	MeshComponent* mesh = new MeshComponent(this);
	mesh->SetTextureIndex(0);
	AddComponent(mesh);
}

void Cube::Update()
{
	Actor::Update();
	/*rotX = 50 * Timer::deltaTime;
	rotY = 50 * Timer::deltaTime;
	GetTransformComponent().RotateX(rotX);
	GetTransformComponent().RotateY(rotY);*/
}

void Cube::Destroy()
{
	Actor::Destroy();
}
