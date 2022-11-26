#pragma once
#include "Timer.h"
#include "SDL.h"

class TimerMuS : public Timer {
public:
	TimerMuS();
	~TimerMuS();

	void Start();
	float Read();

private:
	static Uint64 frequency;
	Uint64 start_time;
};