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
    callback = nullptr;
    selfDestroy = false;
}

Interface::~Interface() {
    if (GetParent() != nullptr) {
        GetParent()->RemoveChild(this);
    }
}

void Interface::EnableSelfDestroy() {
    selfDestroy = true;
}

bool Interface::IsSelfDestroy() {
    return selfDestroy;
}

void Interface::BringToFront() {
    //tmpInterface = MyInterface->uiElements.begin()[pos];
    for (int i = 0; i < uiElements.size(); ++i) {
        if (uiElements.begin()[i] == this) {
            uiElements.erase(uiElements.begin() + i);
            uiElements.push_back(this);
            break;
        }
    }
}

void Interface::VerifyMouseState() {
    if (!isMouseIn) {
        if (mouseX > dstMask.x && mouseX < (dstMask.x + dstMask.w) &&
            mouseY > dstMask.y && mouseY < (dstMask.y + dstMask.h)) {
            OnMouseIn();
            isMouseIn = true;
        }
    }
    else {
        if (!(mouseX > dstMask.x && mouseX < (dstMask.x + dstMask.w) &&
            mouseY > dstMask.y && mouseY < (dstMask.y + dstMask.h))) {
            OnMouseOut();
            isMouseIn = false;
        }
    }
}

bool Interface::IsOnMouseRange() {
    if (mouseX > dstMask.x && mouseX < (dstMask.x + dstMask.w) &&
        mouseY > dstMask.y && mouseY < (dstMask.y + dstMask.h)) {
        return true;
    }
    return false;
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

void Interface::SetCursorFollwing(const bool state){
    if (!isMovable)
        return;

    followCursor = state;
    followingX = mouseX - dstMask.x;
    followingY = mouseY - dstMask.y;
}

void Interface::UpdateFollowingPosition() {
    if (!(isMovable && followCursor))
        return;

    dstMask.x = mouseX - followingX;
    dstMask.y = mouseY - followingY;
}

bool Interface::CheckFocus(const int& x, const int& y) {
    if (x >= dstMask.x && x <= (dstMask.x + dstMask.w) &&
        y >= dstMask.y && y <= (dstMask.y + dstMask.h)) {
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
    int width = GetParent() ? GetParent()->GetSize().x : GetWindowSize().x;
    dstMask.x = (width - dstMask.w) / 2;
}

void Interface::SetVerticalCenterPosition() {
    int height = GetParent() ? GetParent()->GetSize().y : GetWindowSize().y;
    dstMask.y = (height - dstMask.h) / 2;
}

void Interface::SetPosition(const short int &x, const short int &y) {
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


XYPair Interface::GetRelativePosition() {
    XYPair pos = { x, y };
    return pos;
}

void Interface::SetSize(const short int &width, const short int &height) {
    dstMask.w = width;
    dstMask.h = height;
}

XYPair Interface::GetSize() {
    XYPair pos = { dstMask.w, dstMask.h };
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
    if (nullptr != parent) {
        this->parent = parent;
        this->parent->b_isParent = true;
        this->parent->AddChild(this);
    }
}

void Interface::AddChild(Interface* child) {
    childs.push_back(child);
}

void Interface::RemoveChild(Interface* child) {
    for (int i = 0; i < childs.size(); ++i) {
        if (childs.begin()[i] == child) {
            childs.erase(childs.begin() + i);
            break;
        }

    }
}

bool Interface::CheckLeftClick(SDL_MouseButtonEvent& b) {
    Interface* it = nullptr;
    for (int64_t j = childs.size() - 1; j >= 0; --j) {
        it = childs.begin()[j];
        if (it->IsOnMouseRange() && it->isRealShow()) {
            if (it->isParent()) {
                if (!it->CheckLeftClick(b)) {
                    it->OnMouseClick(b);
                    return true;
                }
                else {
                    return false;
                }
            }
            else {
                it->OnMouseClick(b);
                return true;
            }
        }
    }
    return false;
}

void Interface::OnMouseClick(SDL_MouseButtonEvent& b) {
    if (mouseX > dstMask.x && mouseX < (dstMask.x + dstMask.w) &&
        mouseY > dstMask.y && mouseY < (dstMask.y + dstMask.h)) {
        if (b.button == SDL_BUTTON_LEFT)
            OnLeftClick();
        else OnRightClick();
    }
}

void Interface::OnLeftClick() {
    if (callback != nullptr) {
        callback();
    }
}

void Interface::OnRightClick() {
    //cout << "Click dreapta la " << x << " " << y << endl;
}

void Interface::OnKeyPress(bool KEYS[], int currentKey) {
    //if(currentKey == SDLK_a)
        //cout << "Am apasat a: " << currentKey << endl;
}

void Interface::OnKeyRelease(bool KEYS[], int currentKey) {
    //if (currentKey == SDLK_a)
       // cout << "Am ridicat a: " << currentKey << endl;
}

void Interface::SetLeftClickEvent(function<void(void)> callback_func) {
    callback = callback_func;
}


SDL_Rect* Interface::GetDstRectPointer() {
    return &dstMask;
}

bool Interface::isRealShow() {
    Interface* tmp = this;
    while (tmp) {
        if (!tmp->isShow())
            return false;
        tmp = tmp->GetParent();
    }

    return true;
}

XYPair Interface::GetWindowSize() {
    XYPair tmp = {0, 0};
    SDL_GetWindowSize(Window, &tmp.x, &tmp.y);
    return tmp;
}