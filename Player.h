#pragma once
#include "Image.h"
#include "Timer.h"

class Player : public Image {
	bool moving;
	bool direction; // false = left; true = right
	char framesNumber, currentFrame;
	Timer frameTimer;
public:
	Player();
	~Player();
	bool Init();
	void Render();
	void OnKeyPress(bool KEYS[], unsigned int currentKey);
	void OnKeyRelease(bool KEYS[], unsigned int currentKey);
};