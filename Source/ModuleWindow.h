#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "SDL.h"

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow();

	// Destructor
	virtual ~ModuleWindow();

	// Called before quitting
	bool Init();

	update_status Update();

	// Called before quitting
	bool CleanUp();

	int GetResolutionWidth();
	int GetResolutionHeight();

public:
	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The surface contained by the window
	SDL_Surface* screen_surface = NULL;

	float brightness;
	static int current_screen_resolution;
	static int current_window_mode;
};

#endif // __ModuleWindow_H__