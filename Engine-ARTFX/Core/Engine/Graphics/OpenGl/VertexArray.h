#pragma once

constexpr float vertices[] = {
-0.5f, 0.5f, 0.0f,            0.0f, 0.0f,     //top left
0.5f, 0.5f, 0.0f,             1.0f, 0.0f,     //top right
0.5f, -0.5f, 0.0f,            1.0f, 1.0f,     //bottom right
-0.5f, -0.5f, 0.0f,           0.0f, 1.0f };   //bottom left

constexpr unsigned int indices[] = {
0, 1, 2,
2, 3, 0
};

constexpr float cubeVertices[] = {
	// Positions           // Coordonnées de texture
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   // Face avant
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   // Face arrière
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   // Face gauche
	-0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,

	 0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   // Face droite
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   // Face bas
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 0.0f,   // Face haut
	 0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f
};

constexpr unsigned int cubeIndices[] = {
	0, 2, 1,  1, 2, 3,  // Face avant
	4, 5, 6,  5, 7, 6,  // Face arrière
	8, 9, 10, 9, 11, 10, // Face gauche
	12, 13, 14, 13, 15, 14, // Face droite
	16, 17, 18, 17, 19, 18, // Face bas
	20, 21, 22, 21, 23, 22  // Face haut
};


class VertexArray
{
public:
	VertexArray(const float* pVertices, unsigned int pVerticeCount, const unsigned int* pIndices, unsigned int pIndexCount);
	~VertexArray();

	void SetActive();
	unsigned int GetVerticeCount() const
	{
		return mVerticeCount;
	}
	unsigned int GetIndicesCount() const
	{
		return mIndexCount;
	}
private:
	unsigned int mVerticeCount;
	unsigned int mIndexCount;

	unsigned int mVertexArrayId;
	unsigned int mVertexBufferId;
	unsigned int mIndexBufferId;
};