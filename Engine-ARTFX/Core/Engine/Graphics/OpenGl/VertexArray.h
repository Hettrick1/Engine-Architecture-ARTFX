#pragma once

constexpr float spriteVertices[] = {
	//POSITION                      NORMALS                     TEXCOORDS
	-0.5f, 0.5f, 0.0f,              0.0f, 0.0f, 0.0f,           0.0f, 0.0f,     //top left
	0.5f, 0.5f, 0.0f,               0.0f, 0.0f, 0.0f,           1.0f, 0.0f,     //top right
	-0.5f, -0.5f, 0.0f,             0.0f, 0.0f, 0.0f,           0.0f, 1.0f,      //bottom left
	0.5f, -0.5f, 0.0f,              0.0f, 0.0f, 0.0f,           1.0f, 1.0f,     //bottom right
};

class VertexArray
{
public:
	VertexArray(const float* pVertices, unsigned int pVerticeCount);
	~VertexArray();

	void SetActive();
	unsigned int GetVerticeCount() const
	{
		return mVerticeCount;
	}
private:
	unsigned int mVerticeCount;

	unsigned int mVertexArrayId;
	unsigned int mVertexBufferId;
};