#include "CameraComponent.h"
#include "Actor.h"
#include "Vector3D.h"
#include "Log.h"
#include "Matrix4DRow.h"
#include "Scene.h"

CameraComponent::CameraComponent(Actor* pOwner)
	: Component(pOwner)
{

}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::Update()
{
	Component::Update();
	Vector3D camPosition = mOwner->GetTransformComponent().GetPosition();
	Vector3D target = mOwner->GetTransformComponent().GetPosition() + mOwner->GetTransformComponent().Forward() * 100.0f;
	Vector3D up = mOwner->GetTransformComponent().Up();
	Log::Info("" + std::to_string(camPosition.x) + ", " + std::to_string(camPosition.y) + ", " + std::to_string(camPosition.z)); 
	Matrix4DRow view = Matrix4DRow::CreateLookAt(camPosition, target, up); 
	
	mOwner->GetScene().GetRenderer()->SetViewMatrix(view);
}
