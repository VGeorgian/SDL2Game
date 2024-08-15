#pragma once

#include "Image.h"
#include "MenuButton.h"

class Menu : public Image {
	Image* titleImage;

	MenuButton* startButton;
	MenuButton* settingsButton;
	MenuButton* helpButton;
	MenuButton* exitButton;

public:
	void SetStartButtonEvent(function<void(void)> callback_func);
	void SetSettingsButtonEvent(function<void(void)> callback_func);
	void SetHelpButtonEvent(function<void(void)> callback_func);
	void SetExitButtonEvent(function<void(void)> callback_func);
	Menu();
	~Menu();
	bool Init();
};