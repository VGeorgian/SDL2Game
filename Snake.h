#pragma once
#include "Image.h"
#include "Timer.h"
#include "MenuButton.h"

#define FIELD_WIDTH 25
#define FIELD_HEIGHT 15

class Snake : public Image {
	char direction; // 0 = left | 1 = top | 2 = right | 3 = bottom
	Timer timerMoving; // timpul la care sarpele avanseaza un block
	Image* field;
	Image* fruit;
	Image* gameOverScreen;
	Image* startScreen;
	Image* closeButton;
	MenuButton* restartButton;
	MenuButton* startButton;
	TextLine* gameOverText;
	TextLine* scoreText;

	char positionX, positionY; // coordonatele capului sarpelui pe harta
	vector <Image*> snake; // blocurile sarpelui
	bool sprint; // verifica daca sarpele trebuie sa isi mareasca viteza
	bool isStarted;
	bool fruitField[FIELD_WIDTH * FIELD_HEIGHT];
	//vector <int> snake;
public:
	Snake();
	~Snake();

	void OnKeyPress(bool KEYS[], int currentKey);
	void OnKeyRelease(bool KEYS[], int currentKey);
	void Update();

	bool Init();
	void OpenGame();
	void CloseGame();
	void StartGame();
	void GenerateFruit();
};