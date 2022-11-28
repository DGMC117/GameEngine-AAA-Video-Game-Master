#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleRenderExercise;
class ModuleEditor;
class ModuleProgram;
class ModuleDebugDraw;

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

private:

	std::list<Module*> modules;

};

extern Application* App;
