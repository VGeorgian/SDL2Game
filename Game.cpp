#include <iostream>
#include <stack>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Game.h"
#include "Image.h"
#include "config.h"

using namespace std;

Game::Game() {
    menuScreen = nullptr;
    textFPS = nullptr;
    isRunning = true;

	MyInterface = new Interface;
	//MyInterface->Init();
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        isRunning = false;
    }
    else {
        Interface::Window = SDL_CreateWindow("SDL Tutorial",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN
        );

        if (Interface::Window == nullptr) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            isRunning = false;
        }
        else {
            Interface::ScreenSurface = SDL_GetWindowSurface(Interface::Window);
            Interface::renderer = SDL_CreateRenderer(Interface::Window, -1, 0);
            TTF_Init();
            Init();
        }
    }
}

Game::~Game() {
    TTF_Quit();
    SDL_Quit();

    delete MyInterface;
    MyInterface = nullptr;

    delete menuScreen;
    menuScreen = nullptr;
}

void Game::Init() {
    menuScreen = new Image;
    menuScreen->LoadImage("assets/img/menu_background.jpg");
    menuScreen->SetPosition(0, 0);
    menuScreen->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    menuScreen->Show();

    textFPS = new TextLine;
    textFPS->SetFont("assets/font/NerkoOne-Regular.ttf", 20);
    textFPS->SetColor(255, 255, 255);
    textFPS->SetText("FPS: 0");
    textFPS->SetPosition(10, 0);
    textFPS->Show();
}

void Game::Run() {
    int i, currentFPS = 0;
    SDL_Event event;
    stack <Interface*> mystack;
    stack <bool> canRender;
    bool checked[MAX_INTERFACE_ELEMENTS];
    bool b_canRender = true, isRunning = true;

    unsigned int lastRenderTime = 0,
                 currentRenderTime,
                 renderInterval = 1000 / MAX_FPS,
                 tmpTime = SDL_GetTicks();

    while (MyInterface->CheckIfRunning() && isRunning) {
        while (SDL_PollEvent(&event)) {
            /* We are only worried about SDL_KEYDOWN and SDL_KEYUP events */
            switch (event.type) {
            case SDL_KEYDOWN:
                printf("Key press detected\n");
                break;

            case SDL_KEYUP:
                printf("Key release detected\n");
                break;

            case SDL_QUIT:
                isRunning = false;

            default:
                break;
            }
        }

        if (FPS_LIMIT){
            currentRenderTime = SDL_GetTicks();
            if (currentRenderTime > lastRenderTime + renderInterval) {
                ++currentFPS;
                if (currentRenderTime > tmpTime + 1000) {
                    tmpTime = currentRenderTime;
                    //printf("FPS-uri: %d\n", currentFPS);
                    char tmpBuffer[10];
                    snprintf(tmpBuffer, 10, "FPS: %d", currentFPS);
                    textFPS->SetText(tmpBuffer);
                    currentFPS = 1;
                }
                lastRenderTime = currentRenderTime;
                b_canRender = true;
            }
            else b_canRender = false;
        }

        if(b_canRender)
            SDL_RenderClear(Interface::renderer);

        memset(checked, 0, sizeof(bool) * MAX_INTERFACE_ELEMENTS);

        i = 0;
        for (vector<Interface*>::iterator it = MyInterface->uiElements.begin(); it != MyInterface->uiElements.end(); ++it) {
            
            if ((*it)->GetParent() == nullptr) {
                (*it)->CheckPressedKeys();
                (*it)->Update();
                if((*it)->isShow() && b_canRender)
                    (*it)->Render();

                checked[i] = true;

                //Verific daca e parinte si ii caut toti copiii
                if ((*it)->isParent()) {
                    mystack.push((*it));
                    canRender.push((*it)->isShow());

                    for (int j = 0; j < MyInterface->uiElements.size(); ++j) {
                        if (!checked[j]) {
                            if ((*(MyInterface->uiElements.begin() + j))->GetParent() == mystack.top()) {

                                //Verific daca parintii lui sunt afisati
                                if ((*(MyInterface->uiElements.begin() + j))->isParent()) {
                                    if (canRender.top())
                                        canRender.push((*(MyInterface->uiElements.begin() + j))->isShow());
                                    else
                                        canRender.push(false);
                                }

                                (*(MyInterface->uiElements.begin() + j))->CheckPressedKeys();
                                (*(MyInterface->uiElements.begin() + j))->Update();
                                (*(MyInterface->uiElements.begin() + j))->UpdatePosition();

                                //Verific daca parintii lui sunt vizibili
                                //Daca nu are parinti, verific daca el este vizibil
                                if(canRender.top() && (*(MyInterface->uiElements.begin() + j))->isShow())
                                    (*(MyInterface->uiElements.begin() + j))->Render();

                                checked[j] = true;

                                if ((*(MyInterface->uiElements.begin() + j))->isParent()) {
                                    mystack.push((*(MyInterface->uiElements.begin() + j)));
                                   
                                    j = -1;
                                }

                                //Daca s-a ajuns la ultimul element si stiva mai 
                                //are elemente, elimin ultimul element
                                else if (j == MyInterface->uiElements.size() - 1 && !mystack.empty()) {
                                    mystack.pop();
                                    canRender.pop();
                                    j = -1;
                                }
                            }
                        }
                    }
                }
            }
            ++i;
        }

        if (b_canRender)
            SDL_RenderPresent(Interface::renderer);

	}
}
