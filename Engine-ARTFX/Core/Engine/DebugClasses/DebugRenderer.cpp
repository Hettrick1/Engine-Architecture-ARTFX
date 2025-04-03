#include "DebugRenderer.h"
#include "Line.h"
#include "ColliderComponent.h"

DebugRenderer::DebugRenderer()
{
}

DebugRenderer::~DebugRenderer()
{
}

void DebugRenderer::Initialize(Window& pWindow)
{
	mDebugVertex.Load("Debug.vert", ShaderType::VERTEX);
	mDebugFragment.Load("Debug.frag", ShaderType::FRAGMENT);
	mDebugShaderProgram.Compose({ &mDebugVertex, &mDebugFragment });
	mView = Matrix4DRow::CreateLookAt(Vector3D(0, 0, 5), Vector3D::unitX, Vector3D::unitZ);
	mProj = Matrix4DRow::CreatePerspectiveFOV(70.0f, pWindow.GetDimensions().x, pWindow.GetDimensions().y, 0.01f, 10000.0f);
}

void DebugRenderer::Draw(IRenderer& pRenderer)
{
	for (auto& collider : mCollider) // DEBUG ONLY
	{
		collider->DebugDraw(pRenderer);
	}
	for (auto& line : mLines) // DEBUG ONLY
	{
		DrawDebugLine(line->Start, line->End, line->Hit);
	}
	mLines.clear();
}

void DebugRenderer::AddDebugCollider(ColliderComponent* pCol)
{
	mCollider.push_back(pCol);
}

void DebugRenderer::AddDebugLine(Line* pLine)
{
	mLines.push_back(pLine);
}

void DebugRenderer::DrawDebugBox(Vector3D& pMin, Vector3D& pMax, Matrix4DRow pWorldTransform)
{
	GLfloat vertices[] = {
		// Face avant
		0.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,  1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 0.0f,

		// Face arrière
		0.0f, 0.0f, 1.0f,  1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f,

		// Liaisons entre les faces avant et arrière
		0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f,  1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 1.0f
	};

	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	mDebugShaderProgram.Use();
	Matrix4DRow wt = pWorldTransform;
	mDebugShaderProgram.setMatrix4Row("uViewProj", mView * mProj);
	mDebugShaderProgram.setMatrix4Row("uWorldTransform", wt);
	mDebugShaderProgram.setVector3f("uColor", Vector3D(0, 1, 0));
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);

	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, 24);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_DEPTH_TEST);

	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void DebugRenderer::DrawDebugLine(const Vector3D& start, const Vector3D& end, const HitResult& hit)
{
	GLuint debugVAO, debugVBO;
	glGenVertexArrays(1, &debugVAO);
	glGenBuffers(1, &debugVBO);
	glLineWidth(3);

	float lineVertices[] = {
		start.x, start.y, start.z,
		end.x, end.y, end.z
	};

	glBindVertexArray(debugVAO);
	glBindBuffer(GL_ARRAY_BUFFER, debugVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	mDebugShaderProgram.Use();
	mDebugShaderProgram.setMatrix4Row("uViewProj", mView * mProj);
	Matrix4DRow identity = Matrix4DRow::Identity;
	mDebugShaderProgram.setMatrix4Row("uWorldTransform", identity);

	if (hit.HitActor) {
		mDebugShaderProgram.setVector3f("uColor", Vector3D(1, 0, 0)); // Rouge si touché
	}
	else {
		mDebugShaderProgram.setVector3f("uColor", Vector3D(0, 1, 0)); // Vert si non touché
	}

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDrawArrays(GL_LINES, 0, 2);
	glDisable(GL_DEPTH_TEST);

	glDeleteBuffers(1, &debugVBO);
	glDeleteVertexArrays(1, &debugVAO);

	if (hit.HitActor)
	{
		GLuint cubeVAO, cubeVBO;
		glGenVertexArrays(1, &cubeVAO);
		glGenBuffers(1, &cubeVBO);

		const float size = 0.1f;
		Vector3D hitPos = hit.HitPoint;

		// Vertices d'un cube (8 sommets)
		float cubeVertices[] = {
			// Face avant
			hitPos.x - size, hitPos.y - size, hitPos.z + size,
			hitPos.x + size, hitPos.y - size, hitPos.z + size,
			hitPos.x + size, hitPos.y + size, hitPos.z + size,
			hitPos.x - size, hitPos.y + size, hitPos.z + size,

			// Face arrière
			hitPos.x - size, hitPos.y - size, hitPos.z - size,
			hitPos.x + size, hitPos.y - size, hitPos.z - size,
			hitPos.x + size, hitPos.y + size, hitPos.z - size,
			hitPos.x - size, hitPos.y + size, hitPos.z - size
		};

		// Indices pour dessiner les arêtes (12 arêtes)
		unsigned int cubeIndices[] = {
			0,1, 1,2, 2,3, 3,0, // Face avant
			4,5, 5,6, 6,7, 7,4, // Face arrière
			0,4, 1,5, 2,6, 3,7  // Liaisons
		};

		glBindVertexArray(cubeVAO);

		// Buffer pour les vertices
		glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// Buffer pour les indices
		GLuint EBO;
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

		mDebugShaderProgram.Use();
		mDebugShaderProgram.setMatrix4Row("uViewProj", mView * mProj);
		mDebugShaderProgram.setMatrix4Row("uWorldTransform", Matrix4DRow::Identity);
		mDebugShaderProgram.setVector3f("uColor", Vector3D(1, 1, 0)); // Jaune

		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
		glDisable(GL_DEPTH_TEST);

		glDeleteBuffers(1, &EBO);
		glDeleteBuffers(1, &cubeVBO);
		glDeleteVertexArrays(1, &cubeVAO);
	}
}

void DebugRenderer::SetViewMatrix(Matrix4DRow pViewMatrix)
{
	mView = pViewMatrix;
}
