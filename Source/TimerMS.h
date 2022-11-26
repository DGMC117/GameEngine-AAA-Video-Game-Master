#pragma once
#include "Timer.h"
#include "SDL.h"

class TimerMS : public Timer {
public:
	TimerMS();
	~TimerMS();

	void Start();
	float Read();

private:
	Uint32 start_time;
};