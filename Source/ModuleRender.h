#pragma once
#include "Module.h"
#include "Globals.h"
#include "TimerMS.h"
#include "MathGeoLib.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void WindowResized(unsigned width, unsigned height);

	void* GetContext();
	float4x4 GetModelMatrix();
	float4x4 GetViewMatrix();
	float4x4 GetProjectionMatrix();

private:
	void* context;

	TimerMS frame_timer;
};
