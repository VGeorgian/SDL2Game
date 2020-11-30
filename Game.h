#include <SDL.h>
#include "Interface.h"
#include "Image.h"
//#include "SettingsManager.h"

class Game {
private:
	Interface* MyInterface;
	bool isRunning;

	Image* background;
	Image* background2;
	Image* background3;
public:
	Game();
	~Game();
	void Init();
	void Run();
};