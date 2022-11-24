#pragma once
#include "GUIElement.h"

class GUIConsole : public GUIElement {
public:
	GUIConsole(const char* title);
	~GUIConsole();

	void ClearLog();
	void AddLog(const char* message);
	void Draw();

	// Portable helpers
	static char* Strdup(const char* s) { IM_ASSERT(s); size_t len = strlen(s) + 1; void* buf = malloc(len); IM_ASSERT(buf); return (char*)memcpy(buf, (const void*)s, len); }

public:
	bool* con_open = nullptr;

private:
	const char* title;
	ImVector<char*> output;
	ImGuiTextFilter filter;
	bool auto_scroll;
	bool scroll_to_bottom;
};