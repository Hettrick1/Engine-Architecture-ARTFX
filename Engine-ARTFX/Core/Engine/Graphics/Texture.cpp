#include "Texture.h"

Texture::Texture()
	: mHeight(0), mWidth(0), mSdlTexture(nullptr)
{

}

Texture::~Texture()
{
}

bool Texture::Load(Renderer& renderer, const std::string& filename)
{
	mFilePath = filename;
	SDL_Surface* surface = IMG_Load(mFilePath.c_str());
	if (!surface) 
	{
		Log::Error(LogType::Application, "Failed to load texture file :" + mFilePath);
		return false;
	}
	mWidth = surface->w;
	mHeight = surface->h;

	mSdlTexture = SDL_CreateTextureFromSurface(renderer.ToSdlRenderer(), surface);
	SDL_FreeSurface(surface);
	if (!mSdlTexture) {
		Log::Error(LogType::Render, "Failed to convert surface to texture :" + mFilePath);
		return false;
	}
	Log::Info("Loaded texture : " + mFilePath);
	return true;
}

void Texture::Unload()
{
	if (mSdlTexture) SDL_DestroyTexture(mSdlTexture);
}

void Texture::UpdateInfo(int& width, int& height)
{
	width = mWidth;
	height = mHeight;
}

void Texture::OverrideTextureSize(int width, int height)
{
	mWidth = width;
	mHeight = height;
}

Vector2D Texture::GetTextureSize()
{
	return {static_cast<float>(mWidth), static_cast<float>(mHeight)};
}
