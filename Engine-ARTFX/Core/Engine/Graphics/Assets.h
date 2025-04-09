#pragma once

#include "Texture.h"
#include "Mesh.h"
#include <map>
#include <string>
#include "Font.h"

class Assets
{
public:
	static std::map<std::string, Texture> mTextures;
	static std::map<std::string, Mesh*> mMeshes;
	static std::map<std::string, Font> mFonts;
	static Texture* LoadTexture(IRenderer& pRenderer, const std::string& pFilePath, const std::string& pName);
	static Texture& GetTexture(const std::string& pName);
	static Mesh* LoadMesh(const std::string& pFilePath, const std::string& pName);
	static Mesh* GetMesh(const std::string& pName);
	static Font* LoadFont(const std::string& pFilePath, const std::string& pName);
	static Font& GetFont(const std::string& pName);
	static void Clear();
private:
	Assets() = default;
	static Texture LoadTextureFromFile(IRenderer& pRenderer, const std::string& pFilePath);
	static Mesh* LoadMeshFromFile(const std::string& pFilePath);
	static Font LoadFontFromFile(const std::string& pFilePath);

};

