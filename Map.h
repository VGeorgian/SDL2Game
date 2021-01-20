#pragma once
#include "vector"
#include "Image.h"
#include "Player.h"
#include "config.h"
#include "Timer.h"
#include "GameObject.h"
#include "Snake.h"
#include "MenuButton.h"

class Map : public Image {
	Player* player;
	vector<GameObject*> collision;
	Timer movingTime;
	bool movingLeft;
	bool movingRight;
	bool movingTop;
	bool movingBottom;
	Snake* snakeGame;
public:
	Map();
	~Map();
	bool Init();
	void OnKeyPress(bool KEYS[], int currentKey);
	void OnKeyRelease(bool KEYS[], int currentKey);
	void Update();

	bool CheckCollision(const int &x, const int &y);

	void PlaySnake();
	void ShowMap();
	void HideMap();
};