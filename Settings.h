#pragma once
#include "Image.h"
#include "TextLine.h"
#include "MenuButton.h"

class Settings : public Image {
	TextLine* title;
	MenuButton* backButton;
	MenuButton* saveButton;
	TextLine* screenSizeLabel;
	TextLine* musicStatusLabel;
	TextLine* volumeLabel;
public:
	Settings();
	~Settings();
	bool Init();
	void ShowSettings();
};