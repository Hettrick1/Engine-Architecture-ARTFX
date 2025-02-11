#pragma once

#include <iostream>
#include "SDL.h"
#include "..\..\Maths\Vector2D.h"
#include "Renderer.h"

class Texture
{
public:
	Texture();
	~Texture();
	bool Load(Renderer& renderer, const std::string& filename);
	void Unload();
	void UpdateInfo(int& width, int& height);
	Vector2D GetTextureSize();

private:
	std::string mFilePath;
	SDL_Texture* mSdlTexture;
	int mWidth, mHeight;
};