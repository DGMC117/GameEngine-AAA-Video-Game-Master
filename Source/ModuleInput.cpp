#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "SDL.h"
#include "imgui_impl_sdl.h"
#include "ModuleCamera.h"

ModuleInput::ModuleInput()
{}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

    keyW_holdRC = new CameraForwardCommand();
    keyA_holdRC = new CameraLeftCommand();
    keyS_holdRC = new CameraBackwardsCommand();
    keyD_holdRC = new CameraRightCommand();
    keyQ_holdRC = new CameraDownCommand();
    keyE_holdRC = new CameraUpCommand();
    keyUP = new CameraPitchCounterClockwiseCommand();
    keyLEFT = new CameraYawCounterClockwiseCommand();
    keyDOWN = new CameraPitchClockwiseCommand();
    keyRIGHT = new CameraYawClockwiseCommand();

	return ret;
}

// Called every draw update
update_status ModuleInput::Update()
{

    SDL_Event sdlEvent;

    while (SDL_PollEvent(&sdlEvent) != 0)
    {
        switch (sdlEvent.type)
        {
            case SDL_QUIT:
                return UPDATE_STOP;
            case SDL_WINDOWEVENT:
                if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED || sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                    App->renderer->WindowResized(sdlEvent.window.data1, sdlEvent.window.data2);
                break;
        }
        ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
    }

    keyboard = SDL_GetKeyboardState(NULL);

    if (keyboard[SDL_SCANCODE_W]) keyW_holdRC->execute();
    if (keyboard[SDL_SCANCODE_S]) keyS_holdRC->execute();
    if (keyboard[SDL_SCANCODE_A]) keyA_holdRC->execute();
    if (keyboard[SDL_SCANCODE_D]) keyD_holdRC->execute();
    if (keyboard[SDL_SCANCODE_Q]) keyQ_holdRC->execute();
    if (keyboard[SDL_SCANCODE_E]) keyE_holdRC->execute();
    if (keyboard[SDL_SCANCODE_UP]) keyUP->execute();
    if (keyboard[SDL_SCANCODE_LEFT]) keyLEFT->execute();
    if (keyboard[SDL_SCANCODE_DOWN]) keyDOWN->execute();
    if (keyboard[SDL_SCANCODE_RIGHT]) keyRIGHT->execute();

    return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);

    delete keyW_holdRC;
    delete keyA_holdRC;
    delete keyS_holdRC;
    delete keyD_holdRC;
    delete keyQ_holdRC;
    delete keyE_holdRC;
    delete keyUP;
    delete keyLEFT;
    delete keyDOWN;
    delete keyRIGHT;

	return true;
}
