#pragma once

class Timer {
public:
	virtual void Start() = 0;
	virtual float Read() = 0;
};