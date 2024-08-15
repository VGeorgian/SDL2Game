#include "Image.h"
#include "SpaceInvadersEnemy.h"
#include "MenuButton.h"
#include "TextLine.h"
#include "Timer.h"


class SpaceInvaders : public Image {
	Image* closeButton;
	Image* gameField;
	vector<SpaceInvadersEnemy*> enemies;
	vector<Image*> playerAmmo;
	Image* player;
	char direction; // 0 = pe loc | 1 = stanga | 2 = dreapta
	int playerPosition;
	char currentLevel;
	Image* startScreen;
	Image* gameOverScreen;
	MenuButton* startButton;
	MenuButton* restartButton;
	TextLine* scoreText;
	TextLine* levelText;
	int score;
	bool isStarted;

	Timer shootTimer;
public:
	SpaceInvaders();
	~SpaceInvaders();
	bool Init();

	void OpenGame();
	void CloseGame();
	void OnKeyPress(bool KEYS[], int currentKey);
	void OnKeyRelease(bool KEYS[], int currentKey);
	void Update();
	void GenerateEnemies();
	void EndGame();
	void StartGame();
};