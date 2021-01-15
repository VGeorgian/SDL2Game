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
    Game MyGame;

    CHECK(MyGame.Init(), "MyGame.Init()", __LINE__, __FILE__);

    try {
        MyGame.Run();
    }
    catch(const std::exception& e) {
        cout << e.what();
    }

    SDL_FreeSurface(Interface::ScreenSurface);
    SDL_DestroyWindow(Interface::Window);
    SDL_DestroyRenderer(Interface::renderer);
    SDL_Quit();

    return 0;
}