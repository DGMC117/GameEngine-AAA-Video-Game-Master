#pragma once
#include "Module.h"
#include "Globals.h"
#include "TimerMS.h"
#include "Command.h"

typedef unsigned __int8 Uint8;

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status Update();
	bool CleanUp();

private:
	const Uint8 *keyboard = NULL;
	bool mouse_right_button;

	Command *keyW_holdRC = nullptr;
	Command *keyA_holdRC = nullptr;
	Command *keyS_holdRC = nullptr;
	Command *keyD_holdRC = nullptr;
	Command *keyQ_holdRC = nullptr;
	Command *keyE_holdRC = nullptr;
	Command* keyW_holdRC_LSHIFT = nullptr;
	Command* keyA_holdRC_LSHIFT = nullptr;
	Command* keyS_holdRC_LSHIFT = nullptr;
	Command* keyD_holdRC_LSHIFT = nullptr;
	Command* keyQ_holdRC_LSHIFT = nullptr;
	Command* keyE_holdRC_LSHIFT = nullptr;
	Command *keyUP = nullptr;
	Command *keyLEFT = nullptr;
	Command* keyDOWN = nullptr;
	Command* keyRIGHT = nullptr;
	Command* keyM = nullptr;
	Command* keyN = nullptr;
	Command* mouseRIGHT_motionRIGHT = nullptr;
	Command* mouseRIGHT_motionLEFT = nullptr;
	Command* mouseRIGHT_motionUP = nullptr;
	Command* mouseRIGHT_motionDOWN = nullptr;

public:
	SDL_MouseMotionEvent mouse_motion;
};