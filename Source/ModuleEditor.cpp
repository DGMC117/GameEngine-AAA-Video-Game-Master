#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleEditor.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "GUIConsole.h"
#include "GUIAbout.h"
#include "GUIConfiguration.h"
#include "GUIMainMenuBar.h"

using namespace std;

ModuleEditor::ModuleEditor()
{
	gui_elements.push_back(console = new GUIConsole());
	gui_elements.push_back(about = new GUIAbout());
	gui_elements.push_back(config = new GUIConfiguration());
	gui_elements.push_back(main_menu = new GUIMainMenuBar());
}

// Destructor
ModuleEditor::~ModuleEditor()
{
	for (list<GUIElement*>::iterator it = gui_elements.begin(); it != gui_elements.end(); ++it)
		delete* it;
}

// Called before render is available
bool ModuleEditor::Init()
{
	LOG("Init ModuleEditor");

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->GetContext());
	ImGui_ImplOpenGL3_Init("#version 440");

	demo_open = new bool(false);

	return true;
}

update_status ModuleEditor::PreUpdate()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleEditor::Update()
{
	// Draw ImGui Elements
	for (list<GUIElement*>::iterator it = gui_elements.begin(); it != gui_elements.end(); ++it)
		(*it)->Draw();
	if (*demo_open) ImGui::ShowDemoWindow(demo_open);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	delete demo_open;

	return true;
}