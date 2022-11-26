#include "GUIMainMenuBar.h"
#include "Application.h"
#include "ModuleEditor.h"
#include "GUIConsole.h"
#include "GUIAbout.h"

GUIMainMenuBar::GUIMainMenuBar() {}

GUIMainMenuBar::~GUIMainMenuBar() {}

void GUIMainMenuBar::Draw() {
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("View")) {
			ImGui::MenuItem("Console", NULL, App->edit->console->con_open);
			//ImGui::MenuItem("Configuration", NULL, configuration_open);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help")) {
			if (ImGui::MenuItem("Documentation")) App->RequestBrowser(REPO_WIKI_LINK);
			if (ImGui::MenuItem("Download latest")) App->RequestBrowser(REPO_RELEASE_LINK);
			if (ImGui::MenuItem("Report a bug")) App->RequestBrowser(REPO_ISSUES_LINK);
			//ImGui::MenuItem("ImGui Demo", NULL, demo_open);
			ImGui::MenuItem("About", NULL, App->edit->about->about_open);
			ImGui::EndMenu();
		}
	}
	ImGui::EndMainMenuBar();
}