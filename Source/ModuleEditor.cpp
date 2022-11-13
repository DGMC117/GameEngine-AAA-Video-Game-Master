#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleEditor.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

ModuleEditor::ModuleEditor()
{
	editor_console = EditorConsole();
}

// Destructor
ModuleEditor::~ModuleEditor()
{
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

	console_open = new bool;
	*console_open = true;
	demo_open = new bool;
	*demo_open = false;

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
	if (*demo_open) ImGui::ShowDemoWindow(demo_open);

	// Console Window
	if (*console_open) {
		editor_console.Draw("Console", console_open);
	}

	// Main Menu Bar
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("View")) {
			ImGui::MenuItem("Console", NULL, console_open);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help")) {
			ImGui::MenuItem("ImGui Demo", NULL, demo_open);
			if (ImGui::MenuItem("Documentation")) App->RequestBrowser("https://github.com/DGMC117/GameEngine-AAA-Video-Game-Master/wiki");
			if (ImGui::MenuItem("Download latest")) App->RequestBrowser("https://github.com/DGMC117/GameEngine-AAA-Video-Game-Master/releases");
			if (ImGui::MenuItem("Report a bug")) App->RequestBrowser("https://github.com/DGMC117/GameEngine-AAA-Video-Game-Master/issues");
			//if (ImGui::MenuItem("About")) about->SwitchActive();
			ImGui::EndMenu();
		}
	}
	ImGui::EndMainMenuBar();

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

	delete console_open;
	delete demo_open;

	return true;
}