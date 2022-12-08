#include "ModuleTexture.h"

ModuleTexture::ModuleTexture() {}

ModuleTexture::~ModuleTexture() {}

bool ModuleTexture::Init() {
	return true;
}

update_status ModuleTexture::PreUpdate() {
	return UPDATE_CONTINUE;
}

update_status ModuleTexture::Update() {
	return UPDATE_CONTINUE;
}

update_status ModuleTexture::PostUpdate() {
	return UPDATE_CONTINUE;
}

bool ModuleTexture::CleanUp() {
	return true;
}

bool ModuleTexture::LoadTexture(const wchar_t* file_name, TexMetadata* metadata, ScratchImage& texture) {
	HRESULT res = E_FAIL;

	res = LoadFromDDSFile(file_name, DDS_FLAGS_NONE, metadata, texture);
	if (FAILED(res)) res = LoadFromTGAFile(file_name, TGA_FLAGS_NONE, metadata, texture);
	if (FAILED(res)) res = LoadFromWICFile(file_name, WIC_FLAGS_NONE, metadata, texture);
	return SUCCEEDED(res);
}