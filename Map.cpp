#include <iostream>
#include <fstream>
#include "Map.h"

using namespace std;

Map::Map() {
    player = nullptr;
    movingTime.SetDelay(0);
    movingLeft = false;
    movingRight = false;
    movingTop = false;
    movingBottom = false;
    
    snakeGame = nullptr;
}

Map::~Map() {
    if (nullptr != player)
        delete player;
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

    int x, y, w, h;
    char buffer[64];
    GameObject* tmpObject;

    ifstream IN("map.config", ifstream::in);

    while (IN.good()) {
        IN >> x >> y >> w >> h >> buffer;

        tmpObject = new GameObject;
        tmpObject->SetParent(this);
        tmpObject->LoadImage(buffer);
        tmpObject->SetPosition(x, y);
        tmpObject->SetSize(w, h);
        tmpObject->Show();

        collision.push_back(tmpObject);
    }

    GameObject* snakeMachine = new GameObject;
    snakeMachine->SetParent(this);
    snakeMachine->LoadImage(buffer);
    snakeMachine->SetPosition(500, 500);
    snakeMachine->SetSize(150, 300);
    snakeMachine->SetLeftClickEvent(bind(&Map::PlaySnake, this));
    snakeMachine->Show();


    collision.push_back(snakeMachine);

    player = new Player;
    CHECK(player->Init(), "player->Init()", __LINE__, __FILE__);
    //player->SetParent(this);

    snakeGame = new Snake;
    snakeGame->Init();
    snakeGame->Hide();

    return true;
}
void Map::PlaySnake() {
    cout << "Snake game start\n";
    snakeGame->OpenGame();
}

void Map::ShowMap() {
    player->Show();
    this->Show();
}


void Map::OnKeyPress(bool KEYS[], unsigned int currentKey) {
    if (KEYS[SDL_SCANCODE_A]) {
        movingLeft = true;
    }
    if (KEYS[SDL_SCANCODE_D])
        movingRight = true;
    if (KEYS[SDL_SCANCODE_W])
        movingTop = true;
    if (KEYS[SDL_SCANCODE_S])
        movingBottom = true;
}

void Map::OnKeyRelease(bool KEYS[], unsigned int currentKey) {
    if (SDL_SCANCODE_A == currentKey)
        movingLeft = false;
    if (SDL_SCANCODE_D == currentKey)
        movingRight = false;
    if (SDL_SCANCODE_W == currentKey)
        movingTop = false;
    if (SDL_SCANCODE_S == currentKey)
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

        movingTime.SetDelay(1);
    }
}