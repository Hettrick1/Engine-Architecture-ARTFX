#pragma once

#include "../../Maths/Rectangle.h"
#include "../Editor/Window.h"
#include "SDL_image.h"
#include <vector>

class SpriteComponent;
class Actor;
class Texture;

class Renderer
{
public :
	enum class Flip
	{
		None = SDL_FLIP_NONE,
		Horizontal = SDL_FLIP_HORIZONTAL,
		Vertical = SDL_FLIP_VERTICAL
	};

public:
	Renderer();
	Renderer(const Renderer&) = delete;
	Renderer& operator = (const Renderer&) = delete;

	bool Initialize(Window& rWindow);
	void BeginDraw();
	void Draw();
	void EndDraw();
	void Close();

	void AddSprite(SpriteComponent* pSprite);

	void RemoveSprite(SpriteComponent* pSprite);

	void DrawRect(Rectangle& rRect);
	void DrawSprite(Actor& pActor, Texture& pTexture, Rectangle pRect, Vector2D pOrigin, Renderer::Flip pFlipMethod);
	SDL_Renderer* ToSdlRenderer();
private:
	SDL_Renderer* mSdlRenderer;
	std::vector<SpriteComponent*> mSprites;
};

