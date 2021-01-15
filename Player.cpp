#include <iostream>
#include "Player.h"

using namespace std;

Player::Player() {
    srcMask = { 0, 0, 100, 100 };
    moving = false;
    direction = false;
    framesNumber = 6;
    frameTimer.SetDelay(0);
    currentFrame = 0;
}

Player::~Player() {

}

bool Player::Init() {
    CHECK(this->LoadImage("assets/img/player.png"), "player->LoadImage()", __LINE__, __FILE__);
    this->SetPosition(0, 0);
    this->SetSize(100, 100);
    this->SetVerticalCenterPosition();
    this->SetHorizontalCenterPosition();

    return true;
}

void Player::Render() {


    if (moving) {
        if (frameTimer.TimeElasped()) {
            frameTimer.SetDelay(75);
            srcMask.x = 100 * currentFrame;
            srcMask.y = 100 * !direction;

            if (currentFrame == framesNumber - 1)
                currentFrame = 0;
            else ++currentFrame;
        }
    }
    else {
        if (frameTimer.TimeElasped()) {
            frameTimer.SetDelay(250);
            srcMask.x = 100 * currentFrame;
            srcMask.y = 100 * (3 - direction);

            if (currentFrame == framesNumber - 1)
                currentFrame = 0;
            else ++currentFrame;
        }

    }

    if (texture) {
        SDL_RenderCopy(renderer, texture, &srcMask, &dstMask);
    }

}

void Player::OnKeyPress(bool KEYS[], unsigned int currentKey) {
    if (KEYS[SDL_SCANCODE_W] || KEYS[SDL_SCANCODE_S]) {
        if (!moving) {
            moving = true;
            frameTimer.SetDelay(0);
        }
    }

    if (KEYS[SDL_SCANCODE_A]) {
        if (!moving) {
            moving = true;
            frameTimer.SetDelay(0);
        }

        direction = false; // left
    }

    if (KEYS[SDL_SCANCODE_D]) {
        if (!moving) {
            moving = true;
            frameTimer.SetDelay(0);
        }

        direction = true; // right
    }
}

void Player::OnKeyRelease(bool KEYS[], unsigned int currentKey) {

    if (KEYS[SDL_SCANCODE_A] || KEYS[SDL_SCANCODE_D] || KEYS[SDL_SCANCODE_W] || KEYS[SDL_SCANCODE_S]) {
        moving = true;
    }
    else {
        frameTimer.SetDelay(0);
        moving = false;
        currentFrame = 0;
    }

    if (KEYS[SDL_SCANCODE_A]) {
        direction = false; // left
    }

    if (KEYS[SDL_SCANCODE_D]) {
        direction = true; // right
    }
}
