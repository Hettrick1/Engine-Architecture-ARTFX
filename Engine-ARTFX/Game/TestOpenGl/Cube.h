#pragma once
#include "Actor.h"
#include "SpriteComponent.h"

class Cube : public Actor
{
public:
	Cube(Vector3D pPos = 0, Vector3D pSize = 1, Quaternion pRotation = Quaternion(0,0));
	~Cube();
	void Start() override;
	void Update() override;
	void Destroy() override;
};

