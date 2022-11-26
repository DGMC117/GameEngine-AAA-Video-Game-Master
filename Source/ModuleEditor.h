#pragma once

#include<list>
#include "Module.h"
#include "Globals.h"
#include "GUIElement.h"

class GUIConsole;
class GUIAbout;
class GUIConfiguration;
class GUIMainMenuBar;

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
	GUIAbout* about;
	GUIConfiguration* config;
	GUIMainMenuBar* main_menu;

	bool* demo_open = nullptr; // TODO: Development only - delete after final version.

private:

	std::list<GUIElement*> gui_elements;
};