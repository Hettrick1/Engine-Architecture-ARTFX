#pragma once

#include "Scene.h"
#include "Shaders/ShaderProgram.h"

class GlTestScene : public Scene
{
public:
	GlTestScene();
	~GlTestScene();
	void Start(IRenderer* renderer) override;
	void Update() override;
	void Render() override;
	void Close() override;
private:
};

