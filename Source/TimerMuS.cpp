#include "TimerMuS.h"

Uint64 TimerMuS::frequency;

TimerMuS::TimerMuS() {
	frequency = SDL_GetPerformanceFrequency();
}

TimerMuS::~TimerMuS() {}

void TimerMuS::Start() {
	start_time = SDL_GetPerformanceCounter();
}

float TimerMuS::Read() {
	return (float) (SDL_GetPerformanceCounter() - start_time) / frequency;
}