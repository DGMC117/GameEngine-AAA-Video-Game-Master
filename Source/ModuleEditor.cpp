#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleEditor.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "GUIConsole.h"

using namespace std;

ModuleEditor::ModuleEditor()
{
	gui_elements.push_back(console = new GUIConsole("Console"));
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
	about_open = new bool(false);
	configuration_open = new bool(false);
	ms_log = new float[60];
	fps_log = new float[60];
	last_ms_log = SDL_GetTicks();
	fps_offset = 0;

	return true;
}

update_status ModuleEditor::PreUpdate()
{
	unsigned curr_ms_log = SDL_GetTicks();
	ms_log[fps_offset] = curr_ms_log - last_ms_log;
	if (ms_log[fps_offset] == 0) ms_log[fps_offset] = 1;
	fps_log[fps_offset] = 1000 / ms_log[fps_offset];
	last_ms_log = curr_ms_log;

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
	DrawMainMenuBar();
	if (*demo_open) ImGui::ShowDemoWindow(demo_open);
	if (*about_open) DrawAboutWindow();
	if (*configuration_open) DrawConfigurationWindow();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate()
{
	fps_offset++;
	if (fps_offset > 59) fps_offset = 0;
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
	delete about_open;
	delete configuration_open;
	delete ms_log;
	delete fps_log;

	return true;
}

void ModuleEditor::DrawMainMenuBar() {
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("View")) {
			ImGui::MenuItem("Console", NULL, console->con_open);
			ImGui::MenuItem("Configuration", NULL, configuration_open);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help")) {
			ImGui::MenuItem("ImGui Demo", NULL, demo_open);
			if (ImGui::MenuItem("Documentation")) App->RequestBrowser(REPO_WIKI_LINK);
			if (ImGui::MenuItem("Download latest")) App->RequestBrowser(REPO_RELEASE_LINK);
			if (ImGui::MenuItem("Report a bug")) App->RequestBrowser(REPO_ISSUES_LINK);
			ImGui::MenuItem("About", NULL, about_open);
			ImGui::EndMenu();
		}
	}
	ImGui::EndMainMenuBar();
}

void ModuleEditor::DrawAboutWindow() {
	if (ImGui::Begin("About", about_open)) {
		if (ImGui::CollapsingHeader(TITLE)) {
			ImGui::Text("Game Engine developed for the \"Advanced Programming for AAA Video Games\" master's degree.");
			ImGui::Text("Author: David Garcia De Mercado");
		}
		if (ImGui::CollapsingHeader("Libraries")) {
			ImGui::BulletText("SDL 2.0");
			ImGui::BulletText("glew 2.1.0");
			ImGui::BulletText("imgui 1.88");
		}
		if (ImGui::CollapsingHeader("License")) {
			ImGui::Text("MIT License");
		}
		ImGui::End();
	}
}

void ModuleEditor::DrawConfigurationWindow() {
	if (ImGui::Begin("Configuration", configuration_open)) {
		if (ImGui::CollapsingHeader("Application")) {
			char title[50];
			sprintf_s(title, 50, "Framerate (Current) %.1f", fps_log[fps_offset]);
			ImGui::PlotHistogram("##framerateCurr", &fps_log[0], 60, fps_offset, title, 0.0f, 100.0f, ImVec2(310, 100));
			sprintf_s(title, 50, "Milliseconds (Current) %.1f", ms_log[fps_offset]);
			ImGui::PlotHistogram("##millisecondsCurr", &ms_log[0], 60, fps_offset, title, 0.0f, 40.0f, ImVec2(310, 100));
		}
		ImGui::End();
	}
}