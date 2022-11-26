#pragma once
#include "GUIElement.h"

class GUIAbout : public GUIElement {
public:
	GUIAbout();
	~GUIAbout();

	void Draw();

public:
	bool* about_open = nullptr;
};