#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>
#include <conio.h>
#include <vector>
#include "Game.h"

//Init all game components

SDL_Window* Interface::Window = nullptr;

SDL_Surface* Interface::ScreenSurface = nullptr;

SDL_Renderer* Interface::renderer = nullptr;

bool Interface::isRunning = true;

vector <Interface*> Interface::uiElements;

int main(void) {
    Game* MyGame = new Game;

    delete MyGame;
    return 0;
}