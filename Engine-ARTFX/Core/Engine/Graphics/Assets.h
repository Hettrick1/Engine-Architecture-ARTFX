#pragma once

#include "Texture.h"
#include <map>
#include <string>

class Assets
{
public:
	static std::map<std::string, Texture> mTextures;
	static Texture* LoadTexture(Renderer& pRenderer, const std::string& pFilePath, const std::string& pName);
	static Texture& GetTexture(const std::string& pName);
	static void Clear();
private:
	Assets() = default;
	static Texture LoadTextureFromFile(Renderer& pRenderer, const std::string& pFilePath);
};

