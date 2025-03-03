#include "VertexArray.h"
#include "glew.h"

VertexArray::VertexArray(const float* pVertices, unsigned int pVerticeCount, const unsigned int* pIndices, unsigned int pIndexCount)
	: mVerticeCount(pVerticeCount), mIndexCount(pIndexCount), mVertexArrayId(0), mVertexBufferId(0), mIndexBufferId(0)
{
	// VAO
	glGenVertexArrays(1, &mVertexArrayId);
	glBindVertexArray(mVertexArrayId);

	// VBO
	glGenBuffers(1, &mVertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, mVerticeCount * 5 * sizeof(float), pVertices, GL_STATIC_DRAW);

	// EBO
	glGenBuffers(1, &mIndexBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndexCount * sizeof(float), pIndices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBufferId);
	glDeleteBuffers(1, &mIndexBufferId);
	glDeleteBuffers(1, &mVertexArrayId);
}

void VertexArray::SetActive()
{
	glBindVertexArray(mVertexArrayId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferId);
}
