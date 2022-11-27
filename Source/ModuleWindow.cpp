#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"

int ModuleWindow::current_screen_resolution;
int ModuleWindow::current_window_mode;

ModuleWindow::ModuleWindow()
{
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
	LOG("Init SDL window & surface");
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window
		brightness = 1.0f;
		current_screen_resolution = RES_1280_720;
		current_window_mode = BASIC_WINDOW;
		Uint32 flags = SDL_WINDOW_SHOWN |  SDL_WINDOW_OPENGL;

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, GetResolutionWidth(), GetResolutionHeight(), flags);

		if(window == NULL)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

update_status ModuleWindow::Update() {
	// Apply window configuration parameters
	SDL_SetWindowBrightness(window, brightness);
	SDL_SetWindowSize(window, GetResolutionWidth(), GetResolutionHeight());
	switch (current_window_mode) {
	case BORDERLESS_WINDOW:
		SDL_SetWindowBordered(window, SDL_FALSE);
		SDL_SetWindowFullscreen(window, 0);
		break;
	case FULLSCREEN_WINDOW:
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
		break;
	case FULL_DESKTOP_WINDOW:
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		break;
	default:
		SDL_SetWindowBordered(window, SDL_TRUE);
		SDL_SetWindowFullscreen(window, 0);
		break;
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

int ModuleWindow::GetResolutionWidth() {
	switch (current_screen_resolution) {
	case RES_640_360:
		return 640;
	case RES_854_480:
		return 854;
	case RES_1920_1080:
		return 1920;
	case RES_2560_1440:
		return 2560;
	case RES_3840_2160:
		return 3840;
	case RES_7680_4320:
		return 7680;
	default:
		return 1280;
	}
}

int ModuleWindow::GetResolutionHeight() {
	switch (current_screen_resolution) {
	case RES_640_360:
		return 360;
	case RES_854_480:
		return 480;
	case RES_1920_1080:
		return 1080;
	case RES_2560_1440:
		return 1440;
	case RES_3840_2160:
		return 2160;
	case RES_7680_4320:
		return 4320;
	default:
		return 720;
	}
}

