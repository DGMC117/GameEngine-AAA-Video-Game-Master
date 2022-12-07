#include "GUIConsole.h"

GUIConsole::GUIConsole() {
	ClearLog();
	auto_scroll = true;
	scroll_to_bottom = false;
	con_open = new bool(false);
}

GUIConsole::~GUIConsole() {
	ClearLog();
	delete con_open;
}

void GUIConsole::ClearLog() {

	for (int i = 0; i < output.Size; i++) free(output[i]);
	output.clear();
}

void GUIConsole::AddLog(const char* message) {
	output.push_back(Strdup(message));
	if (output.size() > 100) output.erase(output.begin());
}

void GUIConsole::Draw() {
	if (!*con_open) return;
	if (!ImGui::Begin("Console", con_open)) {
		ImGui::End();
		return;
	}

	if (ImGui::BeginPopupContextItem()) {
		if (ImGui::MenuItem("Close Console"))
			*con_open = false;
		ImGui::EndPopup();
	}

	// Options menu
	if (ImGui::BeginPopup("Options")) {
		ImGui::Checkbox("Auto-scroll", &auto_scroll);
		ImGui::EndPopup();
	}

	// Options, Filter
	if (ImGui::Button("Options")) ImGui::OpenPopup("Options");
	ImGui::SameLine();
	filter.Draw("Filter (\"incl,-excl\") (\"notification\")", 180);
	ImGui::Separator();

	if (ImGui::SmallButton("Clear")) { ClearLog(); }
	ImGui::Separator();

	// Reserve enough left-over height for 1 separator + 1 input text
	const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
	if (ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar)) {
		if (ImGui::BeginPopupContextWindow()) {
			if (ImGui::Selectable("Clear")) ClearLog();
			ImGui::EndPopup();
		}

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
		for (int i = 0; i < output.Size; i++) {
			const char* line = output[i];
			if (!filter.PassFilter(line)) continue;

			// TODO: Apply style to text (red = error, yellow = notification...)

			ImGui::TextUnformatted(line);
		}

		if (scroll_to_bottom || (auto_scroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())) ImGui::SetScrollHereY(1.0f);
		scroll_to_bottom = false;

		ImGui::PopStyleVar();
	}
	ImGui::EndChild();

	ImGui::End();
}