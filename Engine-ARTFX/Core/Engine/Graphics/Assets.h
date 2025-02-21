#pragma once

#include "Texture.h"
#include <map>
#include <string>

class Assets
{
public:
	static std::map<std::string, Texture> mTextures;
	static Texture* LoadTexture(IRenderer& pRenderer, const std::string& pFilePath, const std::string& pName);
	static Texture& GetTexture(const std::string& pName);
	static void Clear();
private:
	Assets() = default;
	static Texture LoadTextureFromFile(IRenderer& pRenderer, const std::string& pFilePath);
};

