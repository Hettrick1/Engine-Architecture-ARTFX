#pragma once

#include "Actor.h"
#include "Shaders/Shader.h"
#include "Texture.h"
#include "Shaders/ShaderProgram.h"
#include <vector>
#include "SkySphereComponent.h"
		
class SkySphere : public Actor
{
public:
	SkySphere(std::vector<Texture*> textures = { nullptr }, ShaderProgram* program = nullptr);
	~SkySphere();
	void Start() override;
	void Update() override;
	void Destroy() override;
private:
	ShaderProgram* mShaderProgram;
	SkySphereComponent* mSkySphereComponent;
};