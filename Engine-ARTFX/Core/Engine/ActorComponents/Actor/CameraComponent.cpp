#include "CameraComponent.h"
#include "Actor.h"
#include "Vector3D.h"
#include "Log.h"
#include "Matrix4DRow.h"
#include "CameraManager.h"
#include "Scene.h"

CameraComponent::CameraComponent(Actor* pOwner, int updateOder)
	: Component(pOwner, updateOder)
{
	CameraManager::Instance().AddCamera(this);
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::Update()
{
    Matrix4DRow worldTransform = GetWorldTransform();
    Vector3D camPosition = worldTransform.GetTranslation();
    Vector3D forward = worldTransform.GetYAxis();
    Vector3D target = camPosition + forward * 400.0f;
    Vector3D up = worldTransform.GetZAxis(); // Récupère le vrai "up"

    Matrix4DRow view = Matrix4DRow::CreateLookAt(camPosition, target, up);
    mOwner->GetScene().GetRenderer()->SetViewMatrix(view);
}

