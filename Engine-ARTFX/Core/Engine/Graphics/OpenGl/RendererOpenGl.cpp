#include "RendererOpenGl.h"
#include "SpriteComponent.h"
#include "MeshComponent.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "Maths.h"
#include "Actor.h"
#include "Texture.h"
#include "glew.h"

RendererOpenGl::RendererOpenGl()
	: mVAO(nullptr), mWindow(nullptr), mSpriteShaderProgram(nullptr)
{
}

RendererOpenGl::~RendererOpenGl()
{
	if (mVAO != nullptr) {
		delete mVAO;
	}
	if (mWindow != nullptr) {
		delete mWindow;
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
	mSpriteViewProj = Matrix4DRow::CreateSimpleViewProj(mWindow->GetDimensions().x, mWindow->GetDimensions().y);
	mView = Matrix4DRow::CreateLookAt(Vector3D(0, 0, 5), Vector3D::unitX, Vector3D::unitZ);
	mProj = Matrix4DRow::CreatePerspectiveFOV(70.0f, mWindow->GetDimensions().x, mWindow->GetDimensions().y, 0.01f, 10000.0f);
	return true;
}

void RendererOpenGl::BeginDraw()
{
	glClearColor(0.1f, 0.45f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RendererOpenGl::Draw()
{
	DrawMeshes();
	DrawSprites();
	for (auto& collider : mCollider) // DEBUG ONLY
	{
		collider->DebugDraw(*this);
	}
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
	Matrix4DRow scaleMat = Matrix4DRow::CreateScale(pTexture.GetTextureSize());
	Matrix4DRow world = scaleMat * pActor.GetTransformComponent().GetWorldTransform();
	mSpriteShaderProgram->setMatrix4Row("uWorldTransform", world);
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
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST); 

	glBindVertexArray(VAO); 
	glDrawArrays(GL_LINES, 0, 24);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_DEPTH_TEST); 

	glDeleteBuffers(1, &VBO); 
	glDeleteVertexArrays(1, &VAO);
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
	glDisable(GL_DEPTH_TEST); 
	glEnable(GL_BLEND); 
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	if (mSpriteShaderProgram == nullptr)
	{
		return;
	}
	mSpriteShaderProgram->Use(); 
	mSpriteShaderProgram->setMatrix4Row("uViewProj", mSpriteViewProj); 
	mVAO->SetActive(); 
	for (SpriteComponent* sprite : mSprites) {
		sprite->Draw(*this);
	}
}

void RendererOpenGl::SetSpriteShaderProgram(ShaderProgram& shaderProgram)
{
	mSpriteShaderProgram = &shaderProgram;
	mSpriteShaderProgram->Use();
}
