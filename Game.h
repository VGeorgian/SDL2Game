#include <SDL.h>
#include "Interface.h"
#include "Image.h"
//#include "SettingsManager.h"

class Game {
private:
	Interface* MyInterface;
	bool isRunning;

	Image* menuScreen;
public:
	Game();
	~Game();
	void Init();
	void Run();
};