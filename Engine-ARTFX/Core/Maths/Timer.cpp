#include "Timer.h"

unsigned int Timer::mFrameStart = 0;
unsigned int Timer::mFrameTime = 0;
unsigned int Timer::mLastFrame = 0;
float Timer::deltaTime = 0;

unsigned int Timer::ComputeDeltaTime()
{
    mFrameStart = SDL_GetTicks();
    unsigned int dt = mFrameStart - mLastFrame;
    mLastFrame = mFrameStart;
    dt = std::min(dt, MAX_DT);
    deltaTime = dt / 1000.0f;
    return dt;
}

void Timer::DelayTime()
{
    mFrameTime = SDL_GetTicks() - mFrameStart;
    if (mFrameTime < FRAME_DELAY)
        SDL_Delay(FRAME_DELAY - mFrameTime);
}
