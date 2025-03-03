#include "RendererOpenGl.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "Maths.h"
#include "Actor.h"
#include "Texture.h"
#include "glew.h"

RendererOpenGl::RendererOpenGl()
	: mVAO(nullptr), mWindow(nullptr), mCurrentShaderProgram(nullptr)
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
	mVAO = new VertexArray(vertices, 4, indices, 6);
	mViewProj = Matrix4DRow::CreateSimpleViewProj(mWindow->GetDimensions().x, mWindow->GetDimensions().y);
	return true;
}

void RendererOpenGl::BeginDraw()
{
	glClearColor(0.1f, 0.45f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LESS);
	if (mCurrentShaderProgram == nullptr)
	{
		return;
	}
	mCurrentShaderProgram->Use();
	mCurrentShaderProgram->setMatrix4Row("uViewProj", mViewProj);
	mVAO->SetActive();
}

void RendererOpenGl::Draw()
{
	for (SpriteComponent* sprite : mSprites) {
		sprite->Draw(*this);
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

void RendererOpenGl::DrawSprite(Actor& pActor, Texture& pTexture, Rectangle pRect, Vector2D pOrigin, IRenderer::Flip pFlipMethod) const
{
	if (mCurrentShaderProgram == nullptr)
	{
		return;
	}
	mCurrentShaderProgram->Use();
	Matrix4DRow scaleMat = Matrix4DRow::CreateScale(pTexture.GetTextureSize());
	Matrix4DRow world = scaleMat * pActor.GetTransformComponent().GetWorldTransform();
	mCurrentShaderProgram->setMatrix4Row("uWorldTransform", world);
	pTexture.SetActive();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void RendererOpenGl::SetCurrentShaderProgram(ShaderProgram& shaderProgram)
{
	mCurrentShaderProgram = &shaderProgram;
	mCurrentShaderProgram->Use();
}
