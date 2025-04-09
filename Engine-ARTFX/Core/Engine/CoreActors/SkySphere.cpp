#include "SkySphere.h"

SkySphere::SkySphere(std::vector<Texture*> textures, ShaderProgram* program)
	:mShaderProgram(program), mSkySphereComponent(nullptr)
{

}

SkySphere::~SkySphere()
{
}

void SkySphere::Start()
{
	Actor::Start();
	mSkySphereComponent = new SkySphereComponent(this, false);
}

void SkySphere::Update()
{
	Actor::Update();
}

void SkySphere::Destroy()
{
	Actor::Destroy();
}
