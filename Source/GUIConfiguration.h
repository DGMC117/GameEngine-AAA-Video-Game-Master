#pragma once
#include "GUIElement.h"
#include "TimerMS.h"

class GUIConfiguration : public GUIElement {
public:
	GUIConfiguration();
	~GUIConfiguration();

	void Draw();

public:
	bool* conf_open = nullptr;

	float* frame_ms_log = nullptr;
	float* frame_fps_log = nullptr;
	float* stable_fps_log = nullptr;
	int frame_offset;
	int stable_offset;
	TimerMS frame_timer;
	TimerMS stable_timer;
	int stable_frame_counter;
	int fps_limit;
	bool vsync;
};