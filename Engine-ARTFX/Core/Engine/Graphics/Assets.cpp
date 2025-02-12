#include "Assets.h"
#include <sstream>
#include "Log.h"

std::map<std::string, Texture> Assets::mTextures = {};

Texture Assets::LoadTexture(Renderer& pRenderer, const std::string& pFilePath, const std::string& pName)
{
	mTextures[pName] = LoadTextureFromFile(pRenderer, pFilePath);
	return mTextures[pName];
}

Texture& Assets::GetTexture(const std::string& pName)
{
	if(mTextures.find(pName) == mTextures.end()) {
		std::ostringstream loadError;
		loadError << "Texture " << pName << " does not exists in assets manager\n";
		Log::Error(LogType::Application, loadError.str());
	}
	return mTextures[pName];
}

void Assets::Clear()
{
	for (std::pair<const std::string, Texture>& iter : mTextures)
	{
		iter.second.Unload(); 
	}
	mTextures.clear();
}

Texture Assets::LoadTextureFromFile(Renderer& pRenderer, const std::string& pFilePath)
{
	Texture texture;
	texture.Load(pRenderer, pFilePath);
	return texture;
}
