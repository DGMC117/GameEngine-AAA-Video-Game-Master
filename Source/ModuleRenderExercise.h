#pragma once
#include "Module.h"
#include "Globals.h"
#include "DirectXTex.h"

using namespace DirectX;

class ModuleRenderExercise : public Module
{
public:
	ModuleRenderExercise();
	~ModuleRenderExercise();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

private:
	unsigned vbo;
	unsigned program;
	ScratchImage texture;
	TexMetadata tex_metadata;
	GLuint texture_gl;
};