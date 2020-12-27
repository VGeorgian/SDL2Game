#include <stdio.h>
#include <iostream>
#include <SDL_image.h>
#include "Interface.h"

using namespace std;

Interface::Interface(bool root) {
    parent = nullptr;
    b_isParent = false;
    isVisible = false;
    x = 0; y = 0;
    srcMask = { 0, 0, 0, 0 };
    dstMask = { 0, 0, 0, 0 };
    if(!root)
        uiElements.push_back(this);
    b_isFocusable = false;
    isMovable = false;
    followCursor = false;

    followingX = 0;
    followingY = 0;
    isMouseIn = false;
}

Interface::~Interface() {
    
}

void Interface::VerifyMouseState(const int& x, const int& y) {
    if (!isMouseIn) {
        if (x > dstMask.x && x < (dstMask.x + dstMask.w) &&
            y > dstMask.y && y < (dstMask.y + dstMask.h)) {
            OnMouseIn();
            isMouseIn = true;
        }
    }
    else {
        if (!(x > dstMask.x && x < (dstMask.x + dstMask.w) &&
            y > dstMask.y && y < (dstMask.y + dstMask.h))) {
            OnMouseOut();
            isMouseIn = false;
        }
    }
}

void Interface::OnMouseIn() {
   
}

void Interface::OnMouseOut() {
    
}


void Interface::AddMovableTag() {
    isMovable = true;
}

bool Interface::IsMovable() {
    return isMovable;
}

void Interface::SetCursorFollwing(const bool state, const int& x, const int& y){
    if (!isMovable)
        return;

    followCursor = state;
    followingX = x - dstMask.x;
    followingY = y - dstMask.y;
}

void Interface::UpdateFollowingPosition(const int& x, const int& y) {
    if (!(isMovable && followCursor))
        return;

    dstMask.x = x - followingX;
    dstMask.y = y - followingY;
}

bool Interface::CheckFocus(const int& x, const int& y) {
    if (x > dstMask.x && x < (dstMask.x + dstMask.w) &&
        y > dstMask.y && y < (dstMask.y + dstMask.h)) {
        return true;
    }
    return false;
}

void Interface::SetFocus() {
    b_isFocusable = true;
}

bool Interface::CheckIfRunning() {
	return isRunning;
}

void Interface::SetHorizontalCenterPosition() {
    int width = GetParent() ? GetParent()->GetSize().x : SCREEN_WIDTH;
    dstMask.x = (width - dstMask.w) / 2;
}

void Interface::SetPosition(const short int x, const short int y) {
    XYPair parent_position = { 0, 0 };
    if (this->parent != nullptr) {
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
    if (x > dstMask.x && x < (dstMask.x + dstMask.w) &&
        y > dstMask.y && y < (dstMask.y + dstMask.h)) {
        if (b.button == SDL_BUTTON_LEFT)
            OnLeftClick(x, y);
        else OnRightClick(x, y);
    }
}

void Interface::OnLeftClick(const int& x, const int& y) {
    //cout << "Click stanga la " << x << " " << y << endl;
}

void Interface::OnRightClick(const int& x, const int& y) {
    //cout << "Click dreapta la " << x << " " << y << endl;
}

void Interface::OnKeyPress(bool KEYS[], unsigned int currentKey) {
    //if(currentKey == SDLK_a)
        //cout << "Am apasat a: " << currentKey << endl;
}

void Interface::OnKeyRelease(unsigned int currentKey) {
    //if (currentKey == SDLK_a)
       // cout << "Am ridicat a: " << currentKey << endl;
}