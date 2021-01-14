#pragma once
#include "Image.h"
#include "Timer.h"
#include "MenuButton.h"

#define FIELD_WIDTH 25
#define FIELD_HEIGHT 15

class Snake : public Image {
	char direction; // 0 = left | 1 = top | 2 = right | 3 = bottom
	Timer timerMoving;
	Image* field;
	Image* fruit;
	Image* gameOverScreen;
	Image* startScreen;
	Image* closeButton;
	MenuButton* restartButton;
	MenuButton* startButton;
	char positionX, positionY;
	vector <Image*> snake;
	bool sprint;
	bool isStarted;
public:
	Snake();
	~Snake() {};

	void OnKeyPress(bool KEYS[], unsigned int currentKey);
	void OnKeyRelease(bool KEYS[], unsigned int currentKey);
	void Update();

	bool Init();
	void OpenGame();
	void CloseGame();
	void StartGame();
	void GenerateFruit();
};