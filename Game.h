#pragma once
#include <SDL.h>
#include "Interface.h"
#include "Image.h"
#include "TextLine.h"
#include "Button.h"
//#include "SettingsManager.h"

class Game {
private:
	Interface* MyInterface;
	bool isRunning;

	Image* menuScreen;
	TextLine* textFPS;

	Image* titleImage;

	MenuButton* startButton;
	MenuButton* startButton2;
	MenuButton* startButton3;
	MenuButton* startButton4;
public:
	Game();
	~Game();
	bool Init();
	void Run();

	void StartEvent();
	void ExitEvent();
};