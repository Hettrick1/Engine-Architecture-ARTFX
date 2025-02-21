#pragma once

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "Vector2D.h"
#include "IRenderer.h"

class Texture
{
public:
	Texture();
	~Texture();
	bool Load(IRenderer& renderer, const std::string& filename);
	void Unload();
	void UpdateInfo(int& width, int& height);
	void OverrideTextureSize(int width, int height);
	Vector2D GetTextureSize();
	SDL_Texture* GetSdlTexture() const { return mSdlTexture; }

private:
	std::string mFilePath;
	SDL_Texture* mSdlTexture;
	int mWidth, mHeight;
};