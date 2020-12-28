#pragma once
#include "vector"
#include "Image.h"
#include "Player.h"
#include "config.h"
#include "Timer.h"
#include "GameObject.h"

class Map : public Image {
	Player* player;
	vector<GameObject*> collision;
	Timer movingTime;
	bool movingLeft;
	bool movingRight;
	bool movingTop;
	bool movingBottom;
public:
	Map();
	~Map();
	bool Init();
	void OnKeyPress(bool KEYS[], unsigned int currentKey);
	void OnKeyRelease(unsigned int currentKey);
	void Update();

	bool CheckCollision(const int &x, const int &y);
};