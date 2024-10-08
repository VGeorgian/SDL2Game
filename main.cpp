//#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>
#include <conio.h>
#include <vector>
#include "Game.h"

//Init all game components
bool Interface::isRunning = true;

int Interface::mouseX = 0, Interface::mouseY = 0;

SDL_Window* Interface::Window = nullptr;

SDL_Surface* Interface::ScreenSurface = nullptr;

SDL_Renderer* Interface::renderer = nullptr;


vector <Interface*> Interface::uiElements;

int main(int argc, char* args[]) {
    Game MyGame;

    CHECK(MyGame.Init(), "MyGame.Init()", __LINE__, __FILE__);

    MyGame.Run();

    SDL_FreeSurface(Interface::ScreenSurface);
    SDL_DestroyWindow(Interface::Window);
    SDL_DestroyRenderer(Interface::renderer);
    //TTF_Quit();
    SDL_Quit();

    return 0;
}