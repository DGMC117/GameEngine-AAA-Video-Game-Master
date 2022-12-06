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
	const SDL_MouseButtonEvent *mouse = NULL;

	Command *keyW_holdRC = nullptr;
	Command *keyA_holdRC = nullptr;
	Command *keyS_holdRC = nullptr;
	Command *keyD_holdRC = nullptr;
	Command *keyQ_holdRC = nullptr;
	Command *keyE_holdRC = nullptr;
	Command *keyUP = nullptr;
	Command *keyLEFT = nullptr;
	Command *keyDOWN = nullptr;
	Command *keyRIGHT = nullptr;
};