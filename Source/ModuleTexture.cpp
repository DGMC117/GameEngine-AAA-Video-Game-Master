#include "ModuleTexture.h"
#include "DirectXTex.h"

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