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
	AddComponent(pc);

	mBall = new BowlingBall(0, 1.3);
	mBall->Start();
	mBall->SetPosition(Vector3D(-0.3f, -30.0f, -3.6f));
	mBall->GetComponentOfType<RigidbodyComponent>()->SetMass(5);
	mBall->GetComponentOfType<RigidbodyComponent>()->SetBounciness(0.8);
	mBallSpawnPoint = new BallSpawnPoint(Vector3D(0,-29.5, -1.0), Vector3D(0.1,0.5,0.1));
	mBallSpawnPoint->Start();
	GetScene().AddActor(mBall);
	GetScene().AddActor(mBallSpawnPoint);
	mSpawnPosition = mBall->GetTransformComponent().GetPosition();
}

void BowlingPlayer::Update()
{
	Actor::Update();
	if (mBall->GetRigidBody()->GetVelocity().LengthSq() <= 0.1)
	{
		mBall->SetPosition(mSpawnPosition);
	}
}

void BowlingPlayer::Destroy()
{
	Actor:Destroy();
}

void BowlingPlayer::IncrementIndicatorSize(float strengthPercent)
{
	float y = 2.5 * strengthPercent + 0.5;
	mBallSpawnPoint->GetTransformComponent().SetSize(Vector3D(0.1, y, 0.1));
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
