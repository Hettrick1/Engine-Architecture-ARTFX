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
	Vector3D target = mOwner->GetTransformComponent().GetPosition() + mOwner->GetTransformComponent().Forward() * 400.0f;
	Vector3D up = Vector3D::unitZ;
	//Log::Info("" + std::to_string(camPosition.x) + ", " + std::to_string(camPosition.y) + ", " + std::to_string(camPosition.z)); 
	Matrix4DRow view = Matrix4DRow::CreateLookAt(camPosition, target, up);
	
	mOwner->GetScene().GetRenderer()->SetViewMatrix(view);
}

void CameraComponent::SetRelativeRotation(float pRelRoll, float pRelPitch, float pRelYaw)
{
	mRelRoll = pRelRoll;
	mRelPitch = pRelPitch;
	mRelYaw = pRelYaw;

	float roll = Maths::ToRad(mRelRoll);
	float pitch = Maths::ToRad(mRelPitch);
	float yaw = Maths::ToRad(mRelYaw);

	Quaternion qRoll = Quaternion(Vector3D::unitZ, roll);
	Quaternion qPitch = Quaternion(Vector3D::unitX, pitch);
	Quaternion qYaw = Quaternion(Vector3D::unitY, yaw);

	Quaternion rotation = Quaternion::Concatenate(qYaw, qPitch); 
	rotation = Quaternion::Concatenate(rotation, qRoll); 

	mRelRotation = Quaternion::Concatenate(rotation, mRelRotation);
}
