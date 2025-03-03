#pragma once

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "Vector2D.h"
#include "IRenderer.h"

class RendererSdl;
class RendererOpenGl;

class Texture
{
public:
	Texture();
	~Texture();

	bool Load(IRenderer& pRenderer, const std::string& pFilename);
	void Unload();
	void SetActive() const;
	void UpdateInfo(int& pWidth, int& pHeight);
	void OverrideTextureSize(int pWidth, int pHeight);
	Vector3D GetTextureSize();
	SDL_Texture* GetSdlTexture() const { return mSdlTexture; }

private:
	std::string mFilePath;
	SDL_Texture* mSdlTexture;
	int mWidth, mHeight;
	unsigned int mTextureId;
	bool LoadSdl(RendererSdl* pRenderer, const std::string& pFilePath, SDL_Surface* pSurface);
	bool LoadGl(RendererOpenGl* pRenderer, const std::string& pFilePath, SDL_Surface* pSurface);
};