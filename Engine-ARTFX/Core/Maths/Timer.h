#pragma once

#include <algorithm>
#include <SDL_timer.h>

class Timer
{
public:
	Timer() = default;
	Timer(const Timer&) = delete;
	Timer& operator=(const Timer&) = delete;

	static unsigned int ComputeDeltaTime();
	static void DelayTime();

	static float deltaTime;

private:
	const static unsigned int FPS = 60;
	const static unsigned int FRAME_DELAY = 1000 / FPS;
	//Maximum Delta Time
	const static unsigned int MAX_DT = 50;

	//Time when current frame started
	static unsigned int mFrameStart;
	//Last frame start time 
	static unsigned int mLastFrame;
	//Time needed to run the loop 
	static unsigned int mFrameTime;
};

