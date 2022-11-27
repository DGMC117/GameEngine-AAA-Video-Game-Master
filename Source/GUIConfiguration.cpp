#include "GUIConfiguration.h"
#include "SDL.h"
#include "Application.h"
#include "ModuleWindow.h"

GUIConfiguration::GUIConfiguration() {
	conf_open = new bool(false);

	frame_ms_log = new float[60];
	frame_fps_log = new float[60];
	stable_fps_log = new float[60];
	frame_offset = 0;
	stable_offset = 0;
	frame_timer.Start();
	stable_timer.Start();
	stable_frame_counter = 0;
	vsync = true;
}

GUIConfiguration::~GUIConfiguration() {
	delete conf_open;

	delete frame_ms_log;
	delete frame_fps_log;
	delete stable_fps_log;
}

void GUIConfiguration::Draw() {
	frame_ms_log[frame_offset] = frame_timer.Read();
	if (frame_ms_log[frame_offset] == 0) frame_ms_log[frame_offset] = 1;
	frame_fps_log[frame_offset] = 1000 / frame_ms_log[frame_offset];
	frame_timer.Start();

	if (stable_timer.Read() >= 500.0f) {
		stable_offset++;
		if (stable_offset > 59) stable_offset = 0;
		stable_fps_log[stable_offset] = 2.0f * stable_frame_counter;
	}

	if (*conf_open) {
		if (ImGui::Begin("Configuration", conf_open)) {
			if (ImGui::CollapsingHeader("Application")) {
				char title[50];
				sprintf_s(title, 50, "Framerate (Frame) %.1f", frame_fps_log[frame_offset]);
				ImGui::PlotHistogram("##framerateCurr", &frame_fps_log[0], 60, frame_offset, title, 0.0f, 100.0f, ImVec2(310, 100));
				sprintf_s(title, 50, "Framerate (500ms) %.1f", stable_fps_log[stable_offset]);
				ImGui::PlotHistogram("##framerateStable", &stable_fps_log[0], 60, stable_offset, title, 0.0f, 100.0f, ImVec2(310, 100));
				sprintf_s(title, 50, "Milliseconds (Frame) %.1f", frame_ms_log[frame_offset]);
				ImGui::PlotHistogram("##millisecondsCurr", &frame_ms_log[0], 60, frame_offset, title, 0.0f, 40.0f, ImVec2(310, 100));
				ImGui::Checkbox("Vsync", &vsync);
				ImGui::SliderInt("FPS Limit (0 = no limit)", &fps_limit, 0, 120);
			}
			if (ImGui::CollapsingHeader("Window")) {
				ImGui::SliderFloat("Brightness", &App->window->brightness, 0.0f, 1.0f);
				const char* screen_resolution_name = 
					(App->window->current_screen_resolution >= 0 && App->window->current_screen_resolution < RES_COUNT) ?
					screen_resolution_names[App->window->current_screen_resolution] : "Unknown";
				ImGui::SliderInt("Screen Resolution", &App->window->current_screen_resolution, 0, RES_COUNT - 1, screen_resolution_name);
				ImGui::Separator();
				ImGui::Text("Window Mode");
				ImGui::RadioButton("Basic", &App->window->current_window_mode, BASIC_WINDOW); ImGui::SameLine();
				ImGui::RadioButton("Borderless", &App->window->current_window_mode, BORDERLESS_WINDOW);
				ImGui::RadioButton("Fullscreen", &App->window->current_window_mode, FULLSCREEN_WINDOW); ImGui::SameLine();
				ImGui::RadioButton("Full Desktop", &App->window->current_window_mode, FULL_DESKTOP_WINDOW);
			}
			ImGui::End();
		}
	}

	frame_offset++;
	if (frame_offset > 59) frame_offset = 0;

	if (stable_timer.Read() >= 500.0f) {
		stable_frame_counter = 0;
		stable_timer.Start();
	}
	stable_frame_counter++;
}