#pragma once
#include "vector"
#include "SDL.h"
#include "config.h"

using namespace std;

class Interface {

protected:
	Interface* parent;
	bool b_isParent;
	bool isVisible;
	SDL_Rect srcMask;
	SDL_Rect dstMask;
	int x, y;

public:
	static bool isRunning;

	static SDL_Window* Window;

	static SDL_Surface* ScreenSurface;

	static SDL_Renderer* renderer;

	static vector <Interface*> uiElements;

	Interface();
	~Interface();

	void SetPosition(const short int x, const short int y);
	XYPair GetPosition();

	void SetSize(const short int width, const short int height);
	XYPair GetSize();

	void UpdatePosition();
	void CheckPressedKeys() {};
	virtual void Update() {};
	virtual void Render() {};
	bool CheckIfRunning();
	
	void SetParent(Interface* parent);

	Interface* GetParent() { return parent; };
	bool isParent() { return b_isParent; };
	bool isShow() { return isVisible; };
	void Show() { isVisible = true; };
	void Hide() { isVisible = false; }
};