#pragma once
#include "vector"
#include "SDL.h"
#include "config.h"
// Screens Manager - Loading / Meniu / Game

using namespace std;


class Interface {
	//The window we'll be rendering
protected:
	Interface* parent = nullptr;
	bool b_isParent = false;
	bool isVisible = false;
	SDL_Rect srcMask;
	SDL_Rect dstMask;
	int x, y; //TODO

public:
	static bool isRunning;

	static SDL_Window* Window;

	//The surface contained by the window
	static SDL_Surface* ScreenSurface;

	static SDL_Renderer* renderer;

	static SDL_Texture* texture;

	static vector <Interface*> uiElements;

	Interface();
	~Interface();

	void SetPosition(const short int x, const short int y);
	XYPair GetPosition();

	void SetSize(const short int width, const short int height);
	XYPair GetSize();


	//void Init();
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