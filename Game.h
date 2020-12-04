#include <SDL.h>
#include "Interface.h"
#include "Image.h"
#include "TextLine.h"
//#include "SettingsManager.h"

class Game {
private:
	Interface* MyInterface;
	bool isRunning;

	Image* menuScreen;
	TextLine* textFPS;
public:
	Game();
	~Game();
	bool Init();
	void Run();
};