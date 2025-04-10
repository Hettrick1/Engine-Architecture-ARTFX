#include "SkySphere.h"

SkySphere::SkySphere(bool isSphere,std::vector<std::string> textures, ShaderProgram* program)
	:mShaderProgram(program), mSkySphereComponent(nullptr), mTextureToLoad(textures), mIsSphere(isSphere)
{

}

SkySphere::~SkySphere()
{
}

void SkySphere::Start()
{
	Actor::Start();
	mSkySphereComponent = new SkySphereComponent(this, mIsSphere, mTextureToLoad);
}

void SkySphere::Update()
{
	Actor::Update();
}

void SkySphere::Destroy()
{
	Actor::Destroy();
}
