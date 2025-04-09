#pragma once

#include "Scene.h"
#include "Shaders/ShaderProgram.h"
#include "HudElements/HudText.h"

class SplashScreen : public Scene
{
public:
	SplashScreen();
	~SplashScreen();
	void Start(IRenderer* renderer) override;
	void Update() override;
	void Render() override;
	void Close() override;
private:
	HudText* mZephyrusText;
	HudText* mStudioText;
	float mTime;
};