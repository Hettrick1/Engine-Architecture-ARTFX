#include "Game.h"

Game::Game(std::string title, std::vector<Scene*> scenes) : mIsRunning(true), mAllScenes(scenes)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
    }
    else
    {
        std::cout << "SDL initialization succeeded!";
    }

    mLoadedScene = 0;

    Initialize();

}

Game::~Game()
{
}

void Game::Initialize()
{
    mGameWindow = new Window(800, 800);
    mRenderer = new Renderer();
    if (mGameWindow->Open() && mRenderer->Initialize(*mGameWindow)) Loop();
}

void Game::Loop()
{
    if (mAllScenes.size() > 0) {
        mAllScenes[mLoadedScene]->Start(mRenderer);
    }

    while (mIsRunning) {
        mAllScenes[mLoadedScene]->Update();
        mAllScenes[mLoadedScene]->Render();
        Input();
    }

    Close();
}

void Game::Update()
{
}

void Game::Render()
{
    mRenderer->BeginDraw();
    Rectangle rect = { {250, 300}, {300, 200} };
    mRenderer->DrawRect(rect);
    mRenderer->EndDraw();
}

void Game::Input()
{
    if (mIsRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            mAllScenes[mLoadedScene]->OnInput(event);
            switch (event.type) {
            case SDL_QUIT:
                mIsRunning = false;
                break;
            }
        }
    }
}

void Game::Close()
{
    mGameWindow->Close();
}
