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
    keyW_holdRC_LSHIFT = new CameraForwardFastCommand();
    keyA_holdRC_LSHIFT = new CameraLeftFastCommand();
    keyS_holdRC_LSHIFT = new CameraBackwardsFastCommand();
    keyD_holdRC_LSHIFT = new CameraRightFastCommand();
    keyQ_holdRC_LSHIFT = new CameraDownFastCommand();
    keyE_holdRC_LSHIFT = new CameraUpFastCommand();
    keyUP = new CameraPitchCounterClockwiseCommand();
    keyLEFT = new CameraYawCounterClockwiseCommand();
    keyDOWN = new CameraPitchClockwiseCommand();
    keyRIGHT = new CameraYawClockwiseCommand();
    keyM = new CameraRollCounterClockwiseCommand();
    keyN = new CameraRollClockwiseCommand();
    mouseRIGHT_motionRIGHT = new CameraYawCounterClockwiseMouseCommand();
    mouseRIGHT_motionLEFT = new CameraYawClockwiseMouseCommand();
    mouseRIGHT_motionUP = new CameraPitchCounterClockwiseMouseCommand();
    mouseRIGHT_motionDOWN = new CameraPitchClockwiseMouseCommand();

    mouse_right_button = false;

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
            case SDL_MOUSEBUTTONDOWN:
                if (sdlEvent.button.button == SDL_BUTTON_RIGHT) mouse_right_button = true;
                break;
            case SDL_MOUSEBUTTONUP:
                if (sdlEvent.button.button == SDL_BUTTON_RIGHT) mouse_right_button = false;
                break;
            case SDL_MOUSEMOTION:
                mouse_motion = sdlEvent.motion;
                if (mouse_right_button) {
                    if (mouse_motion.xrel < 0) keyLEFT->execute();
                    else if (mouse_motion.xrel > 0) keyRIGHT->execute();
                    if (mouse_motion.yrel < 0) keyUP->execute();
                    else if (mouse_motion.yrel > 0) keyDOWN->execute();
                }
                break;
        }
        ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
    }

    keyboard = SDL_GetKeyboardState(NULL);

    if (mouse_right_button) {
        if (keyboard[SDL_SCANCODE_W]) (keyboard[SDL_SCANCODE_LSHIFT] ? keyW_holdRC_LSHIFT->execute() : keyW_holdRC->execute());
        if (keyboard[SDL_SCANCODE_S]) (keyboard[SDL_SCANCODE_LSHIFT] ? keyS_holdRC_LSHIFT->execute() : keyS_holdRC->execute());
        if (keyboard[SDL_SCANCODE_A]) (keyboard[SDL_SCANCODE_LSHIFT] ? keyA_holdRC_LSHIFT->execute() : keyA_holdRC->execute());
        if (keyboard[SDL_SCANCODE_D]) (keyboard[SDL_SCANCODE_LSHIFT] ? keyD_holdRC_LSHIFT->execute() : keyD_holdRC->execute());
        if (keyboard[SDL_SCANCODE_Q]) (keyboard[SDL_SCANCODE_LSHIFT] ? keyQ_holdRC_LSHIFT->execute() : keyQ_holdRC->execute());
        if (keyboard[SDL_SCANCODE_E]) (keyboard[SDL_SCANCODE_LSHIFT] ? keyE_holdRC_LSHIFT->execute() : keyE_holdRC->execute());
    }
    if (keyboard[SDL_SCANCODE_UP]) keyUP->execute();
    if (keyboard[SDL_SCANCODE_LEFT]) keyLEFT->execute();
    if (keyboard[SDL_SCANCODE_DOWN]) keyDOWN->execute();
    if (keyboard[SDL_SCANCODE_RIGHT]) keyRIGHT->execute();
    if (keyboard[SDL_SCANCODE_M]) keyM->execute();
    if (keyboard[SDL_SCANCODE_N]) keyN->execute();

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
    delete keyW_holdRC_LSHIFT;
    delete keyA_holdRC_LSHIFT;
    delete keyS_holdRC_LSHIFT;
    delete keyD_holdRC_LSHIFT;
    delete keyQ_holdRC_LSHIFT;
    delete keyE_holdRC_LSHIFT;
    delete keyUP;
    delete keyLEFT;
    delete keyDOWN;
    delete keyRIGHT;
    delete keyM;
    delete keyN;

	return true;
}
