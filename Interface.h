#pragma once
#include <functional>
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
	bool b_isFocusable;
	bool isMovable;
	bool followCursor;
	int followingX, followingY;
	bool isMouseIn;
	std::function<void(void)> callback;
	bool selfDestroy; // Distrugere automata dupa randare
	vector <Interface*> childs;

public:
	static bool isRunning;

	static SDL_Window* Window;

	static SDL_Surface* ScreenSurface;

	static SDL_Renderer* renderer;

	static vector <Interface*> uiElements;

	Interface(bool root = false);
	virtual ~Interface();

	void SetVerticalCenterPosition();
	void SetHorizontalCenterPosition();
	void SetPosition(const short int x, const short int y);
	XYPair GetPosition();
	XYPair GetRelativePosition();

	void SetSize(const short int width, const short int height);
	XYPair GetSize();

	void UpdatePosition();
	void CheckPressedKeys() {};
	virtual void Update() {};
	virtual void Render() {};
	bool CheckIfRunning();
	
	void SetParent(Interface* parent);
	void AddChild(Interface* child);

	Interface* GetParent() { return parent; };
	bool isParent() { return b_isParent; };
	bool isShow() { return isVisible; };
	bool isRealShow();
	void Show() { isVisible = true; };
	void Hide() { isVisible = false; }

	void OnMouseClick(SDL_MouseButtonEvent& b, const int &x, const int &y);
	virtual void OnLeftClick(const int& x, const int& y);
	virtual void OnRightClick(const int& x, const int& y);
	virtual void SetLeftClickEvent(function<void(void)> callback_func);

	bool CheckFocus(const int& x, const int& y);
	void SetFocus();
	bool IsFocusable() { return b_isFocusable; };
	void BringToFront();

	void AddMovableTag();
	bool IsMovable();
	void SetCursorFollwing(const bool state, const int& x = 0, const int& y = 0);
	void UpdateFollowingPosition(const int& x, const int& y);

	void VerifyMouseState(const int& x = 0, const int& y = 0);
	virtual void OnMouseIn();
	virtual void OnMouseOut();
	bool IsOnMouseRange(const int& x = 0, const int& y = 0);
	bool CheckLeftClick(SDL_MouseButtonEvent& b, int& mouseX, int& mouseY); // functie recursiva care cauta toti copiii si verifica daca sunt in raza de randare;

	virtual void OnKeyPress(bool KEYS[], unsigned int currentKey);
	virtual void OnKeyRelease(bool KEYS[], unsigned int currentKey);

	void EnableSelfDestroy();
	bool IsSelfDestroy();
	
	SDL_Rect* GetDstRectPointer();
};