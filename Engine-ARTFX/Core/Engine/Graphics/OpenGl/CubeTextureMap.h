#pragma once
#include "Texture.h"

class CubeTextureMap
{
public:

	bool CreateCubeTextureMap(const std::vector<std::string>& cube_face_paths);
	inline unsigned int GetID() const { return mTextureId; }
	void SetActive() const;
private:
	int mWidth, mHeight;
	unsigned int mTextureId;
	std::vector<std::string> mCubeFacePaths;
};