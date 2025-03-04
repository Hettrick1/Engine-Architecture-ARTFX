#include "Game.h"
#include "Defs.h"
#include "RendererSdl.h"
#include "RendererOpenGl.h"

Game::Game(std::string title, std::vector<Scene*> scenes) 
    : mIsRunning(true), mAllScenes(scenes), mInputManager(InputManager::Instance()), mCollisionManager(CollisionManager::Instance())
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
    delete mRenderer;
    delete mGameWindow;
}

void Game::Initialize()
{
    mGameWindow = new Window(WINDOW_WIDTH, WINDOW_HEIGHT);
    mRenderer = new RendererOpenGl();
    if (mGameWindow->Open() && mRenderer->Initialize(*mGameWindow)) {
        mAllScenes[mLoadedScene]->Load();
        Loop();
    }
}

void Game::Loop()
{
    if (mAllScenes.size() > 0) {
        mAllScenes[mLoadedScene]->Start(mRenderer);
    }
    else {
        Log::Error(LogType::Error, "No scene are available !");
        return;
    }

    while (mIsRunning) {
        Timer::ComputeDeltaTime();
        Input();
        Update(); 
        Render();
        Timer::DelayTime();
    }

    Close();
}

void Game::Update()
{
    mCollisionManager.CheckCollisions();
    mAllScenes[mLoadedScene]->Update();
}

void Game::Render()
{
    mAllScenes[mLoadedScene]->Render();
}

void Game::Input()
{
    if (mIsRunning) {  
        while (SDL_PollEvent(&mSdlEvent)) { 
            switch (mSdlEvent.type) {
            case SDL_QUIT:
                mIsRunning = false;
                break;
            case SDL_KEYDOWN:
                if (mSdlEvent.key.keysym.sym == SDLK_ESCAPE) {
                    mIsRunning = false;
                    break;
                }
            }
            mInputManager.Update();

        }
    }
}

void Game::Close()
{
    mGameWindow->Close();
}
