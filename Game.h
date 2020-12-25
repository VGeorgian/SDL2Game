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

	Image* board;
	Image* board2;
	Image* board3;
	TextLine* boardText;
	TextLine* boardText2;
public:
	Game();
	~Game();
	bool Init();
	void Run();
};