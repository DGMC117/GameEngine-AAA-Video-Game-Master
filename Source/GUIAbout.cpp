#include "GUIAbout.h"

GUIAbout::GUIAbout() {
	about_open = new bool(false);
}

GUIAbout::~GUIAbout() {
	delete about_open;
}

void GUIAbout::Draw() {
	if (!*about_open) return;
	if (ImGui::Begin("About", about_open)) {
		if (ImGui::CollapsingHeader(TITLE)) {
			ImGui::Text("Game Engine developed for the \"Advanced Programming for AAA Video Games\" master's degree.");
			ImGui::Text("Author: David Garcia De Mercado");
		}
		if (ImGui::CollapsingHeader("Libraries")) {
			ImGui::BulletText("SDL 2.0");
			ImGui::BulletText("glew 2.1.0");
			ImGui::BulletText("imgui 1.88");
			ImGui::BulletText("MathGeoLib 1.5");
			ImGui::BulletText("DirectXTex October 2022");
			ImGui::BulletText("assimp 5.2.5");
		}
		if (ImGui::CollapsingHeader("License")) {
			ImGui::Text("MIT License");
		}
		ImGui::End();
	}
}