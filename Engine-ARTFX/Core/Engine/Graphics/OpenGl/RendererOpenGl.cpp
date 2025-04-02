#include "RendererOpenGl.h"
#include "SpriteComponent.h"
#include "MeshComponent.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "Maths.h"
#include "Actor.h"
#include "Texture.h"
#include "glew.h"
#include "HudManager.h"
#include "TextRenderer.h"

RendererOpenGl::RendererOpenGl()
	: mVAO(nullptr), mWindow(nullptr), mSpriteShaderProgram(nullptr), mHud(nullptr)
{
}

RendererOpenGl::~RendererOpenGl()
{
	if (mVAO != nullptr) {
		delete mVAO;
	}
	if (mWindow) {
		SDL_GL_DeleteContext(mContext);
		mWindow = nullptr;
	}
}

bool RendererOpenGl::Initialize(Window& pWindow)
{
	mWindow = &pWindow;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	mContext = SDL_GL_CreateContext(mWindow->GetSdlWindow());
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		Log::Error(LogType::Video, "Failed to initialize glew");
		return false;
	}
	glGetError();

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		Log::Error(LogType::Video, "Failed to initialize SDL_Image");
	}

	mSpriteVertexShader.Load("Simple.vert", ShaderType::VERTEX); 
	mSpriteFragmentShader.Load("Simple.frag", ShaderType::FRAGMENT);  
	mSpriteShaderProgramTemp.Compose({ &mSpriteVertexShader, &mSpriteFragmentShader });
	SetSpriteShaderProgram(mSpriteShaderProgramTemp);

	mSpriteVertexShader.Load("Debug.vert", ShaderType::VERTEX);
	mSpriteFragmentShader.Load("Debug.frag", ShaderType::FRAGMENT);
	mDebugShaderProgram.Compose({ &mSpriteVertexShader, &mSpriteFragmentShader });

	mVAO = new VertexArray(spriteVertices, 4);
	mSpriteViewProj = Matrix4DRow::CreateOrtho(static_cast<float>(pWindow.GetDimensions().x), static_cast<float>(pWindow.GetDimensions().y), 0.000001f, 100000);
	mView = Matrix4DRow::CreateLookAt(Vector3D(0, 0, 5), Vector3D::unitX, Vector3D::unitZ);
	mProj = Matrix4DRow::CreatePerspectiveFOV(70.0f, mWindow->GetDimensions().x, mWindow->GetDimensions().y, 0.01f, 10000.0f);

	mHud = new HudManager();

	//SDL_GL_SetSwapInterval(0); // deactivate V-Sync

	return true;
}

void RendererOpenGl::BeginDraw()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RendererOpenGl::Draw()
{
	DrawMeshes();
	for (auto& collider : mCollider) // DEBUG ONLY
	{
		collider->DebugDraw(*this);
	}
	for (auto& line : mLines) // DEBUG ONLY
	{
		DrawDebugLine(line->Start, line->End, line->Hit);
	}
	mLines.clear();
	DrawSprites();
	DrawHud();
}

void RendererOpenGl::EndDraw()
{
	SDL_GL_SwapWindow(mWindow->GetSdlWindow());
}

void RendererOpenGl::Close()
{
	SDL_GL_DeleteContext(mContext);
	delete mVAO;
}

void RendererOpenGl::AddSprite(SpriteComponent* pSprite)
{
	int spriteDrawOrder = pSprite->GetDrawOrder();
	std::vector<SpriteComponent*>::iterator sc;
	for (sc = mSprites.begin(); sc != mSprites.end(); ++sc)
	{
		if (spriteDrawOrder < (*sc)->GetDrawOrder())
		{
			break;
		}
	}
	mSprites.insert(sc, pSprite);
}

void RendererOpenGl::RemoveSprite(SpriteComponent* pSprite)
{
	std::vector<SpriteComponent*>::iterator sc; 
	sc = std::find(mSprites.begin(), mSprites.end(), pSprite); 
	mSprites.erase(sc); 
}

void RendererOpenGl::AddMesh(MeshComponent* pMesh)
{
	mMeshes.push_back(pMesh);
}

void RendererOpenGl::RemoveMesh(MeshComponent* pMesh)
{
	std::vector<MeshComponent*>::iterator sc; 
	sc = std::find(mMeshes.begin(), mMeshes.end(), pMesh);
	mMeshes.erase(sc); 
}

void RendererOpenGl::AddDebugCollider(ColliderComponent* pCol)
{
	mCollider.push_back(pCol);
}

void RendererOpenGl::AddDebugLine(Line* pLine)
{
	mLines.push_back(pLine);
}

void RendererOpenGl::SetViewMatrix(Matrix4DRow pViewMatrix)
{
	mView = pViewMatrix;
}

void RendererOpenGl::DrawSprite(Actor& pActor, Texture& pTexture, Rectangle pRect, Vector2D pOrigin, IRenderer::Flip pFlipMethod) const
{
	if (mSpriteShaderProgram == nullptr)
	{
		return;
	}
	mSpriteShaderProgram->Use();
	pTexture.SetActive();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void RendererOpenGl::DrawDebugBox(Vector3D& pMin, Vector3D& pMax, Matrix4DRow pWorldTransform)
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

void RendererOpenGl::DrawDebugLine(const Vector3D& start, const Vector3D& end, const HitResult& hit)
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

void RendererOpenGl::DrawMeshes()
{
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	for (MeshComponent* m : mMeshes) 
	{
		m->Draw(mView * mProj);
	}
}

void RendererOpenGl::DrawSprites()
{
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	if (mSpriteShaderProgram == nullptr)
	{
		return;
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	mSpriteShaderProgram->Use(); 
	mSpriteShaderProgram->setMatrix4Row("uViewProj", mView * mProj);
	mVAO->SetActive(); 
	for (SpriteComponent* sprite : mSprites) {
		Matrix4DRow world = sprite->GetWorldTransform();
		mSpriteShaderProgram->setMatrix4Row("uWorldTransform", world);
		sprite->Draw(*this);
	}
}

void RendererOpenGl::DrawHud()
{
	glEnable(GL_CULL_FACE); 
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	mHud->Draw(*this); 
	glDisable(GL_CULL_FACE); 
	glDisable(GL_BLEND); 
}

void RendererOpenGl::DrawHudImage(Texture& pTexture, Rectangle pRect, Vector2D pOrigin)
{
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	if (mSpriteShaderProgram == nullptr)
	{
		return;
	}

	mSpriteShaderProgram->Use();
	mSpriteShaderProgram->setMatrix4Row("uViewProj", mSpriteViewProj);
	Vector3D adjustedPosition = Vector3D(
		pRect.position.x - (pOrigin.x * pRect.dimensions.x),
		pRect.position.y - (pOrigin.y * pRect.dimensions.y),
		0
	);
	Matrix4DRow scaleMat = Matrix4DRow::CreateScale(Vector3D(pRect.dimensions.x, pRect.dimensions.y, 0));
	Matrix4DRow world = scaleMat * Matrix4DRow::CreateTranslation(adjustedPosition);
	mSpriteShaderProgram->setMatrix4Row("uWorldTransform", world);
	mVAO->SetActive();
	pTexture.SetActive();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void RendererOpenGl::SetSpriteShaderProgram(ShaderProgram& shaderProgram)
{
	mSpriteShaderProgram = &shaderProgram;
	mSpriteShaderProgram->Use();
}

void RendererOpenGl::SetHud(HudManager* pHud)
{
	mHud = pHud;
}
