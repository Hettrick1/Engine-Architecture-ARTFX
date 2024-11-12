#include "Pong.h"


Pong::Pong() : Scene()
{
    mPlayerPos = { 200, 200 };
    mPlayer = { mPlayerPos, { 50, 50 } };
}

void Pong::Start(Renderer* renderer) 
{
	Scene::Start(renderer);
}

void Pong::Update()
{
}

void Pong::Render()
{
    mRenderer->BeginDraw();
    mRenderer->DrawRect(mPlayer);
    mRenderer->EndDraw();
}

void Pong::OnInput(SDL_Event event)
{
    switch (event.type) {
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_w) {
            mPlayerPos.y -= 1;
        }
        if (event.key.keysym.sym == SDLK_s) {
            mPlayerPos.y += 1;
        }
        if (event.key.keysym.sym == SDLK_d) {
            mPlayerPos.x += 1;
        }
        if (event.key.keysym.sym == SDLK_a) {
            mPlayerPos.x -= 1;
        }
        mPlayer = { mPlayerPos, { 50, 50 } };
        break;
    }
}

void Pong::Close()
{
}
