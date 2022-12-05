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
    delta_timer.Start();
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::Update()
{
    float delta_time = delta_timer.Read() / 1000.0f;
    delta_timer.Start();

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

    if (keyboard[SDL_SCANCODE_W]) {
        App->camera->TranslateForward(delta_time * 2.0f);
    }
    if (keyboard[SDL_SCANCODE_S]) {
        App->camera->TranslateForward(delta_time * -2.0f);
    }
    if (keyboard[SDL_SCANCODE_A]) {
        App->camera->TranslateSide(delta_time * 2.0f);
    }
    if (keyboard[SDL_SCANCODE_D]) {
        App->camera->TranslateSide(delta_time * -2.0f);
    }
    if (keyboard[SDL_SCANCODE_Q]) {
        App->camera->TranslateVerticalAbs(delta_time * -2.0f);
    }
    if (keyboard[SDL_SCANCODE_E]) {
        App->camera->TranslateVerticalAbs(delta_time * 2.0f);
    }
    if (keyboard[SDL_SCANCODE_LEFT]) {
        App->camera->Yaw(delta_time * -15.0f);
    }
    if (keyboard[SDL_SCANCODE_RIGHT]) {
        App->camera->Yaw(delta_time * 15.0f);
    }
    if (keyboard[SDL_SCANCODE_UP]) {
        App->camera->Pitch(delta_time * -15.0f);
    }
    if (keyboard[SDL_SCANCODE_DOWN]) {
        App->camera->Pitch(delta_time * 15.0f);
    }

    return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
