#include "GameObject.h"

GameObject::GameObject(){

}

GameObject::~GameObject() {

}

bool GameObject::isCollision(const SDL_Rect* rect, const int& x, const int& y) {
	if (CheckFocus(rect->x - x, rect->y - y))
		return true;

	if (CheckFocus(rect->x + rect->w - x, rect->y - y))
		return true;

	if (CheckFocus(rect->x - x, rect->y + rect->h - y))
		return true;

	if (CheckFocus(rect->x + rect->w - x, rect->y + rect->h - y))
		return true;

	return false;
}