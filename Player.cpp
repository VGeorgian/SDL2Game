#include <iostream>
#include "Player.h"

using namespace std;

Player::Player() {
    this->LoadImage("assets/img/player.png");
    this->SetPosition(0, 0);
    this->SetSize(50, 80);
    this->SetVerticalCenterPosition();
    this->SetHorizontalCenterPosition();
    this->Show();
}

Player::~Player() {

}

