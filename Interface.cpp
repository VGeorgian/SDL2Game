#include <stdio.h>
#include <iostream>
#include <SDL_image.h>
#include "Interface.h"

using namespace std;

Interface::Interface() {
    parent = nullptr;
    b_isParent = false;
    isVisible = false;
    x = 0; y = 0;
    srcMask = { 0, 0, 0, 0 };
    dstMask = { 0, 0, 0, 0 };
    uiElements.push_back(this);
}

Interface::~Interface() {
    
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

void Interface::OnMouseClick(SDL_MouseButtonEvent& b, const int &x, const int &y) {
    if (b.button == SDL_BUTTON_LEFT)
        OnLeftClick(x, y);
    else OnRightClick(x, y);
}

void Interface::OnLeftClick(const int& x, const int& y) {
    cout << "Click stanga la " << x << " " << y << endl;
}

void Interface::OnRightClick(const int& x, const int& y) {
    cout << "Click dreapta la " << x << " " << y << endl;
}

void Interface::OnKeyPress(bool KEYS[], unsigned int currentKey) {
    if(currentKey == SDLK_a)
        cout << "Am apasat a: " << currentKey << endl;
}

void Interface::OnKeyRelease(unsigned int currentKey) {
    if (currentKey == SDLK_a)
        cout << "Am ridicat a: " << currentKey << endl;
}