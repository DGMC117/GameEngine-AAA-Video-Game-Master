#include "TimerMS.h"

TimerMS::TimerMS() {}

TimerMS::~TimerMS() {}

void TimerMS::Start() {
	start_time = SDL_GetTicks();
}

float TimerMS::Read() {
	float res = (float)SDL_GetTicks() - start_time;
	if (res < 1.0f) return 1.0f;
	return res;
}