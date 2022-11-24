#pragma once

#include<list>
#include "Module.h"
#include "Globals.h"
#include "GUIElement.h"

class GUIConsole;

class ModuleEditor : public Module
{
public:
	ModuleEditor();
	~ModuleEditor();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	void DrawMainMenuBar();
	void DrawAboutWindow();
	void DrawConfigurationWindow();

public:
	GUIConsole* console;

private:

	std::list<GUIElement*> gui_elements;

	bool *demo_open = nullptr;
	bool *about_open = nullptr;
	bool *configuration_open = nullptr;
	float *ms_log = nullptr;
	float *fps_log = nullptr;
	unsigned last_ms_log;
	int fps_offset;
};