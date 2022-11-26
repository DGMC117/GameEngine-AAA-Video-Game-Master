#include "TimerMS.h"

TimerMS::TimerMS() {}

TimerMS::~TimerMS() {}

void TimerMS::Start() {
	start_time = SDL_GetTicks();
}

float TimerMS::Read() {
	return (float) SDL_GetTicks() - start_time;
}