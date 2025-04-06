#include "BowlingPlayer.h"
#include "BowlingPC.h"
#include "CameraComponent.h"
#include "Scene.h"

BowlingPlayer::BowlingPlayer()
	: Actor(), mBall(nullptr), mBallSpawnPoint(nullptr)
{
}

BowlingPlayer::~BowlingPlayer()
{
	if (mBall != nullptr)
	{
		mBall->Destroy();
	}
	if (mBallSpawnPoint != nullptr)
	{
		mBallSpawnPoint->Destroy();
	}
}

void BowlingPlayer::Start()
{
	Actor::Start();
	CameraComponent* cc = new CameraComponent(this);
	BowlingPC* pc = new BowlingPC(this, 100);
	pc->SetMovementSpeed(5);

	mBall = new BowlingBall(0.0f, 1.3f);
	mBall->Start();
	mBall->SetPosition(Vector3D(-0.3f, -30.0f, -3.6f));
	mBall->GetComponentOfType<RigidbodyComponent>()->SetMass(5);
	mBall->GetComponentOfType<RigidbodyComponent>()->SetBounciness(0.8f);
	mBallSpawnPoint = new BallSpawnPoint(Vector3D(0.0f,-29.5f, -1.0f), Vector3D(0.1f, 0.5f, 0.1f));
	mBallSpawnPoint->Start();
	GetScene().AddActor(mBall);
	GetScene().AddActor(mBallSpawnPoint);
	mSpawnPosition = mBall->GetTransformComponent().GetPosition();
}

void BowlingPlayer::Update()
{
	Actor::Update();
	if (mBall->GetRigidBody()->GetVelocity().LengthSq() <= 0.1f)
	{
		mBall->SetPosition(mSpawnPosition);
	}
}

void BowlingPlayer::Destroy()
{
	Actor::Destroy();
}

void BowlingPlayer::IncrementIndicatorSize(float strengthPercent)
{
	float y = 2.5f * strengthPercent + 0.5f;
	mBallSpawnPoint->GetTransformComponent().SetSize(Vector3D(0.1f, y, 0.1f));
}

void BowlingPlayer::MoveSpawnPointX(float x)
{
	Vector3D spawnPoint = Vector3D(x, mBallSpawnPoint->GetTransformComponent().GetPosition().y, mBallSpawnPoint->GetTransformComponent().GetPosition().z);
	mSpawnPosition.x = x;
	mBallSpawnPoint->SetPosition(spawnPoint);
}

void BowlingPlayer::ThrowBowlingBall(float strengthPercent)
{
	Vector3D impulseDirection(1, 0, 0);

	Quaternion rotation = mBallSpawnPoint->GetTransformComponent().GetRotation();

	Vector3D rotatedDirection = rotation * impulseDirection;

	float strength = 240.0f * strengthPercent;
	Vector3D impulse = rotatedDirection * strength;

	mBall->SetPosition(mSpawnPosition);
	mBall->GetComponentOfType<RigidbodyComponent>()->AddImpulse(impulse);
}

void BowlingPlayer::RotateSpawnPointZ(float axis)
{
	mBallSpawnPoint->GetTransformComponent().RotateZ(axis);
}
