#pragma once
#include <functional>
#include "vector"
#include "SDL.h"
#include "AbstractInterface.h"
#include "config.h"

using namespace std;

class Interface : public AbstractInterface {

protected:
	Interface* parent;
	bool b_isParent;
	bool isVisible;
	SDL_Rect srcMask;
	SDL_Rect dstMask;
	int x, y;
	bool b_isFocusable;
	bool isMovable; 
	bool followCursor; // urmarire cursor
	int followingX, followingY; 
	bool isMouseIn;
	std::function<void(void)> callback; // Callback pt leftclick
	bool selfDestroy; // Distrugere automata dupa randare
	vector <Interface*> childs;

public:
	static bool isRunning;

	static SDL_Window* Window;

	static SDL_Surface* ScreenSurface;

	static SDL_Renderer* renderer;

	static vector <Interface*> uiElements;

	static int mouseX, mouseY;

	Interface(bool root = false);
	virtual ~Interface();

	void SetVerticalCenterPosition();
	void SetHorizontalCenterPosition();
	void SetPosition(const short int &x, const short int &y);
	XYPair GetPosition();
	XYPair GetRelativePosition();
	static XYPair GetWindowSize();

	void SetSize(const short int &width, const short int &height);
	XYPair GetSize();

	void UpdatePosition();
	void Update() {};
	void Render() {};
	bool CheckIfRunning();
	void RenderChilds();
	
	void SetParent(Interface* parent);
	void AddChild(Interface* child);
	void RemoveChild(Interface* child);

	Interface* GetParent() { return parent; };
	bool isParent() { return b_isParent; };
	bool isShow() { return isVisible; };
	bool isRealShow();
	void Show() { isVisible = true; };
	void Hide() { isVisible = false; }

	void OnMouseClick(SDL_MouseButtonEvent& b);
	virtual void OnMouseRelease() {};
	virtual void OnLeftClick();
	virtual void OnRightClick();
	virtual void SetLeftClickEvent(function<void(void)> callback_func);

	bool CheckFocus(const int& x, const int& y);
	void SetFocus();
	bool IsFocusable() { return b_isFocusable; };
	void BringToFront();
	void BringChildToFront(Interface* child);

	void AddMovableTag();
	bool IsMovable();
	void SetCursorFollwing(const bool state);
	void UpdateFollowingPosition();

	void VerifyMouseState();
	virtual void OnMouseIn();
	virtual void OnMouseOut();
	bool IsOnMouseRange();
	bool CheckLeftClick(SDL_MouseButtonEvent& b); // functie recursiva care cauta toti copiii si verifica daca sunt in raza de randare;

	virtual void OnKeyPress(bool KEYS[], int currentKey);
	virtual void OnKeyRelease(bool KEYS[], int currentKey);

	void EnableSelfDestroy();
	bool IsSelfDestroy();
	
	SDL_Rect* GetDstRectPointer();
};