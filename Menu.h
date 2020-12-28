#pragma once

#include "Image.h"
#include "MenuButton.h"

class Menu : public Image {
	Image* titleImage;

public:
	MenuButton* startButton;
	MenuButton* optionButton;
	MenuButton* helpButton;
	MenuButton* exitButton;

	Menu();
	~Menu();
	bool Init();
};