#include "Globals.h"
#include "ModuleEditor.h"

ModuleEditor::ModuleEditor()
{
}

// Destructor
ModuleEditor::~ModuleEditor()
{
}

// Called before render is available
bool ModuleEditor::Init()
{
	LOG("Init ModuleEditor");

	return true;
}

update_status ModuleEditor::PreUpdate()
{
	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleEditor::Update()
{

	return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate()
{
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEditor::CleanUp()
{
	LOG("Destroying ModuleEditor");

	return true;
}