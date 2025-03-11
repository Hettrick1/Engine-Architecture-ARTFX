#include "Assets.h"
#include <sstream>
#include "Log.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "MeshLoader/tiny_obj_loader.h"

std::map<std::string, Texture> Assets::mTextures = {};
std::map<std::string, Mesh*> Assets::mMeshes = {};

Texture* Assets::LoadTexture(IRenderer& pRenderer, const std::string& pFilePath, const std::string& pName)
{
	mTextures[pName] = LoadTextureFromFile(pRenderer, pFilePath);
	return &mTextures[pName];
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

Mesh* Assets::LoadMesh(const std::string& pFilePath, const std::string& pName)
{
	mMeshes[pName] = LoadMeshFromFile(pFilePath);
	return mMeshes[pName];
}

void Assets::Clear()
{
	for (std::pair<const std::string, Texture>& iter : mTextures)
	{
		iter.second.Unload(); 
	}
	mTextures.clear();
}

Texture Assets::LoadTextureFromFile(IRenderer& pRenderer, const std::string& pFilePath)
{
	Texture texture;
	texture.Load(pRenderer, pFilePath);
	return texture;
}

Mesh* Assets::LoadMeshFromFile(const std::string& pFilePath)
{
	Mesh loaded; 
	tinyobj::attrib_t attributes; 
	std::vector<tinyobj::shape_t> shapes; 
	std::vector<tinyobj::material_t> materials; 
	std::string warning, errors; 
	std::string dir = "Meshes/"; 
	bool success = tinyobj::LoadObj(&attributes, &shapes, &materials, &warning, &errors, + pFilePath.c_str());
	if (!success) 
	{
		Log::Error(LogType::Application, "Mesh " + pFilePath + " does not exist or is not .obj");
		return new Mesh();
	}
	else
	{
		Log::Info("Mesh " + pFilePath + " successfully loaded");
	}
	std::vector<Vertex> vertices;
	for (int i = 0; i < shapes.size(); i++)
	{
		tinyobj::shape_t& shape = shapes[i];
		tinyobj::mesh_t& mesh = shape.mesh;
		for (int j = 0; j < mesh.indices.size(); j++)
		{
			tinyobj::index_t i = mesh.indices[j];
			Vector3D position = Vector3D{
				attributes.vertices[i.vertex_index * 3],
				attributes.vertices[i.vertex_index * 3 + 1],
				attributes.vertices[i.vertex_index * 3 + 2]
			};
			Vector3D normal = Vector3D{
				attributes.normals[i.normal_index * 3],
				attributes.normals[i.normal_index * 3 + 1],
				attributes.normals[i.normal_index * 3 + 2]
			};
			Vector2D texCoord = {
				attributes.texcoords[i.texcoord_index * 2],
				attributes.texcoords[i.texcoord_index * 2 + 1],
			};
			Vertex vert = { position, normal, texCoord };
			vertices.push_back(vert);
		}

	}
	return new Mesh(vertices);
}
