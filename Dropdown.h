#pragma once
#include "Image.h"
#include "TextLine.h"
#include "ResolutionItem.h"

class Dropdown : public Image {
	TextLine* currentResolution;
	Image* dropdownContent;
	int currentWidth, currentHeight;
public:
	Dropdown();
	~Dropdown();

	bool Init();
	void ToggleDropdown();

	void SetResolution(int width, int height);
	XYPair GetResolution();

};