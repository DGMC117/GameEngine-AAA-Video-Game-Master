#pragma once
#include "Module.h"
#include "Globals.h"
#include "DirectXTex.h"

using namespace DirectX;

class ModuleTexture : public Module {
public:
	ModuleTexture();
	~ModuleTexture();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	bool LoadTexture(const wchar_t* file_name, TexMetadata *metadata, ScratchImage & texture);
};