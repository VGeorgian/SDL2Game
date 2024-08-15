#pragma once
#include "Image.h"
#include "TextLine.h"
#include "MenuButton.h"
#include "RangeInput.h"
#include "Checkbox.h"
#include "Dropdown.h"

class Settings : public Image {
	TextLine* title;
	MenuButton* saveButton;
	TextLine* screenSizeLabel;
	TextLine* musicStatusLabel;
	TextLine* volumeLabel;

	RangeInput* volumeRange;
	Checkbox* musicCheckbox;
	Dropdown* resolutionDropdown;

	XYPair currentResolution;
	bool musicPlaying;
	int musicVolume;



public:
	Settings();
	~Settings();
	bool Init();
	void ShowSettings();
	void ReadSettingsFromFile();
	void SaveSettings();
};