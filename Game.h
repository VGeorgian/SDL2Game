#pragma once
#include <SDL.h>
#include "Interface.h"
#include "Image.h"
#include "TextLine.h"
#include "Menu.h"
#include "Map.h"
#include "Settings.h"
//#include "SettingsManager.h"

class Game {
private:
	Interface* MyInterface;
	bool isRunning;

	TextLine* textFPS;
	Image* titleImage;

	Menu* gameMenu;
	Map* gameMap;
	Settings* gameSettings;

public:
	Game();
	~Game();
	bool Init();
	void Run();

	void StartEvent();
	void ExitEvent();
};