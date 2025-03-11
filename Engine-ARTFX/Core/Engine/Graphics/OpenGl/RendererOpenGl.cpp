#include "RendererOpenGl.h"
#include "SpriteComponent.h"
#include "MeshComponent.h"
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
