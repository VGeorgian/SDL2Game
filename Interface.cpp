#include <stdio.h>
#include <iostream>
#include <SDL_image.h>
#include "Interface.h"

using namespace std;

Interface::Interface() {
    x = 0; y = 0;
    srcMask = { 0, 0, 0, 0 };
    dstMask = { 0, 0, 0, 0 };
    uiElements.push_back(this);
}

Interface::~Interface() {
    SDL_FreeSurface(ScreenSurface);
    ScreenSurface = nullptr;

    //Destroy window
    SDL_DestroyWindow(Window);
    Window = nullptr;

    //Quit SDL subsystems
    SDL_Quit();
}

bool Interface::CheckIfRunning() {
	return isRunning;
}

void Interface::SetPosition(const short int x, const short int y) {
    XYPair parent_position = { 0, 0 };
    if (parent != nullptr) {
        parent_position = this->parent->GetPosition();
    }
    dstMask.x = x + parent_position.x;
    dstMask.y = y + parent_position.y;
    this->x = x;
    this->y = y;
}

XYPair Interface::GetPosition() {
    XYPair pos = { dstMask.x, dstMask.y };
    return pos;
}

void Interface::SetSize(const short int width, const short int height) {
    dstMask.w = width;
    dstMask.h = height;
}

XYPair Interface::GetSize() {
    XYPair pos = { dstMask.x, dstMask.y };
    return pos;
}

void Interface::UpdatePosition() {
    if (parent != nullptr) {
        XYPair parent_position = this->parent->GetPosition();
        dstMask.x = x + parent_position.x;
        dstMask.y = y + parent_position.y;
    }
}

void Interface::SetParent(Interface* parent) {
    this->parent = parent;
    this->parent->b_isParent = true;
}