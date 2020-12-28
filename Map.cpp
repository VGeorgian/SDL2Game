#include <iostream>
#include "Map.h"

using namespace std;

Map::Map() {
    player = nullptr;
    movingTime.SetDelay(0);
    movingLeft = false;
    movingRight = false;
    movingTop = false;
    movingBottom = false;

    GameObject* tmpObject = new GameObject;
    tmpObject->LoadImage("assets/img/object-red.png");
    tmpObject->SetPosition(0, 0);
    tmpObject->SetParent(this);
    tmpObject->SetSize(400, 10);
    tmpObject->Show();

    collision.push_back(tmpObject);

    tmpObject = new GameObject;
    tmpObject->LoadImage("assets/img/object-red.png");
    tmpObject->SetPosition(0, 0);
    tmpObject->SetParent(this);
    tmpObject->SetSize(10, 400);
    tmpObject->Show();


    collision.push_back(tmpObject);

    tmpObject = new GameObject;
    tmpObject->LoadImage("assets/img/object-red.png");
    tmpObject->SetPosition(400, 0);
    tmpObject->SetParent(this);
    tmpObject->SetSize(10, 400);
    tmpObject->Show();

    collision.push_back(tmpObject);

    tmpObject = new GameObject;
    tmpObject->LoadImage("assets/img/object-red.png");
    tmpObject->SetPosition(0, 400);
    tmpObject->SetParent(this);
    tmpObject->SetSize(130, 10);
    tmpObject->Show();

    collision.push_back(tmpObject);

    tmpObject = new GameObject;
    tmpObject->LoadImage("assets/img/object-red.png");
    tmpObject->SetPosition(400-130, 400);
    tmpObject->SetParent(this);
    tmpObject->SetSize(130, 10);
    tmpObject->Show();

    collision.push_back(tmpObject);
}

Map::~Map() {

}

bool Map::CheckCollision(const int& x, const int& y) {
    SDL_Rect* rect;
    for (auto it : collision) {
        if (it->isCollision(player->GetDstRectPointer(), x, y))
            return true;
        rect = it->GetDstRectPointer(); // Masca obiect
        if (player->CheckFocus(rect->x + x, rect->y + y))
            return true;

        if (player->CheckFocus(rect->x + rect->w + x, rect->y + y))
            return true;

        if (player->CheckFocus(rect->x + x, rect->y + rect->h + y))
            return true;

        if (player->CheckFocus(rect->x + rect->w + x, rect->y + rect->h + y))
            return true;
    }

    return false;
}

bool Map::Init() {
    CHECK(this->LoadImage("assets/img/map.png"), "menuScreen->LoadImage()", __LINE__, __FILE__);
    this->SetPosition(0, 0);
    this->SetSize(3840, 2160);
    this->Show();

    player = new Player;
    //player->SetParent(this);
    player->Show();

    return true;
}


void Map::OnKeyPress(bool KEYS[], unsigned int currentKey) {
    if (KEYS[SDLK_a]) {
        movingLeft = true;
        //cout << "Left";
    }
    if (KEYS[SDLK_d])
        movingRight = true;
    if (KEYS[SDLK_w])
        movingTop = true;
    if (KEYS[SDLK_s])
        movingBottom = true;
}

void Map::OnKeyRelease(unsigned int currentKey) {
    if (SDLK_a == currentKey)
        movingLeft = false;
    if (SDLK_d == currentKey)
        movingRight = false;
    if (SDLK_w == currentKey)
        movingTop = false;
    if (SDLK_s == currentKey)
        movingBottom = false;
}

void Map::Update() {
    if (movingTime.TimeElasped()) {

        if (movingRight && !CheckCollision(-1, 0))
            this->SetPosition(dstMask.x - 1, dstMask.y);
        if (movingLeft && !CheckCollision(1, 0)) {
            this->SetPosition(dstMask.x + 1, dstMask.y);
        }
        if (movingTop && !CheckCollision(0, 1))
            this->SetPosition(dstMask.x, dstMask.y + 1);
        if (movingBottom && !CheckCollision(0, -1))
            this->SetPosition(dstMask.x, dstMask.y - 1);

        
        movingTime.SetDelay(4);
    }
}