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

	console_open = new bool(true);
	demo_open = new bool(false);
	about_open = new bool(false);
	configuration_open = new bool(false);
	ms_log = new float[60];
	fps_log = new float[60];
	last_ms_log = SDL_GetTicks();

	return true;
}

update_status ModuleEditor::PreUpdate()
{
	for (int i = 0; i < 59; ++i) {
		ms_log[i] = ms_log[i + 1];
		fps_log[i] = fps_log[i + 1];
	}
	unsigned curr_ms_log = SDL_GetTicks();
	ms_log[59] = curr_ms_log - last_ms_log;
	if (ms_log[59] == 0) ms_log[59] = 1;
	fps_log[59] = 1000 / ms_log[59];
	last_ms_log = curr_ms_log;

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
			ImGui::MenuItem("Configuration", NULL, configuration_open);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help")) {
			ImGui::MenuItem("ImGui Demo", NULL, demo_open);
			if (ImGui::MenuItem("Documentation")) App->RequestBrowser("https://github.com/DGMC117/GameEngine-AAA-Video-Game-Master/wiki");
			if (ImGui::MenuItem("Download latest")) App->RequestBrowser("https://github.com/DGMC117/GameEngine-AAA-Video-Game-Master/releases");
			if (ImGui::MenuItem("Report a bug")) App->RequestBrowser("https://github.com/DGMC117/GameEngine-AAA-Video-Game-Master/issues");
			ImGui::MenuItem("About", NULL, about_open);
			ImGui::EndMenu();
		}
	}
	ImGui::EndMainMenuBar();

	// About Window
	if (*about_open) {
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

	// Configuration Window
	if (*configuration_open) {
		if (ImGui::Begin("Configuration", configuration_open)) {
			if (ImGui::CollapsingHeader("Application")) {
				char title[25];
				sprintf_s(title, 25, "Framerate %.1f", fps_log[59]);
				ImGui::PlotHistogram("##framerate", &fps_log[0], 60, 0, title, 0.0f, 100.0f, ImVec2(310, 100));
				sprintf_s(title, 25, "Milliseconds %.1f", ms_log[59]);
				ImGui::PlotHistogram("##milliseconds", &ms_log[0], 60, 0, title, 0.0f, 40.0f, ImVec2(310, 100));
			}
			ImGui::End();
		}
	}

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
	delete about_open;
	delete configuration_open;
	delete ms_log;
	delete fps_log;

	return true;
}