#pragma once
#include "SDL.h"
#include "Image.h"

class GameObject: public Image {

public:
	bool isCollision(const SDL_Rect* rect, const int &x, const int &y);
};