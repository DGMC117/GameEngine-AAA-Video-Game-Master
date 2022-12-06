#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"
#include "TimerMS.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleRenderExercise;
class ModuleEditor;
class ModuleProgram;
class ModuleDebugDraw;
class ModuleCamera;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

	void RequestBrowser(const char* url);

public:
	ModuleRender* renderer = nullptr;
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleEditor* edit = nullptr;
	ModuleProgram* program = nullptr;
	ModuleRenderExercise* exercise = nullptr;
	ModuleDebugDraw* debug_draw = nullptr;
	ModuleCamera* camera = nullptr;

	float delta_time;

private:

	std::list<Module*> modules;

	TimerMS delta_timer;

};

extern Application* App;
