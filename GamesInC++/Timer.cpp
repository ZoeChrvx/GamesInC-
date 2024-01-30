#include "Timer.h"
#include <SDL_timer.h>
#include <algorithm>

Timer::Timer() :frameStart(0), lastFrame(0), frameTime(0) {

}

unsigned int Timer::ComputeDeltaTime() {
	frameStart = SDL_GetTicks();
	unsigned int dt = frameStart - lastFrame;
	lastFrame = frameStart;
	return std::min(dt, maxDT);
}

void Timer::DelayTime() {
	frameTime = SDL_GetTicks() - frameStart;
	if (frameTime < frameDelay) {
		SDL_Delay(frameDelay - frameTime);
	}
}
