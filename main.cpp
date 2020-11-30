#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>
#include <conio.h>
#include <vector>
#include "Game.h"

//Init of all game comonents

SDL_Window* Interface::Window = nullptr;

SDL_Surface* Interface::ScreenSurface = nullptr;

SDL_Renderer* Interface::renderer = nullptr;

SDL_Texture* Interface::texture = nullptr;

bool Interface::isRunning = true;

vector <Interface*> Interface::uiElements; // TO DO

int main(void) {

    Game* MyGame = new Game;

    MyGame->Run();

    delete MyGame;
    return 0;
}