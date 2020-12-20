#include <iostream>
#include <stack>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Game.h"
#include "Image.h"
#include "config.h"

using namespace std;

bool Game::Init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        CHECK_ERROR(false, "SDL-ul nu s-a putut initializa", SDL_GetError(), __LINE__, __FILE__);
    }

    Interface::Window = SDL_CreateWindow("SDL Tutorial",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    CHECK_ERROR(Interface::Window, "Eroare la initializarea ferestrei", TTF_GetError(), __LINE__, __FILE__);

    Interface::ScreenSurface = SDL_GetWindowSurface(Interface::Window);
    CHECK_ERROR(Interface::ScreenSurface, "Eroare la initializarea suprafetei", SDL_GetError(), __LINE__, __FILE__);

    Interface::renderer = SDL_CreateRenderer(Interface::Window, -1, 0);
    CHECK_ERROR(Interface::renderer, "Eroare la initializarea renderer-ului", SDL_GetError(), __LINE__, __FILE__);

    if (TTF_Init() == -1) {
        CHECK_ERROR(false, "Eroare la initializarea font-ului", TTF_GetError(), __LINE__, __FILE__);
    }
    // TODO: Verificare init in main si apelare run
    //return false;


    MyInterface = new Interface;

    menuScreen = new Image;
    CHECK(menuScreen->LoadImage("assets/img/menu_background.jpg"), "menuScreen->LoadImage()", __LINE__, __FILE__);
    menuScreen->SetPosition(0, 0);
    menuScreen->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    menuScreen->Show();

    textFPS = new TextLine;
    textFPS->SetFont("assets/font/NerkoOne-Regular.ttf", 20);
    textFPS->SetColor(255, 255, 255);
    textFPS->SetText("FPS: 0");
    textFPS->SetPosition(10, 0);
    textFPS->Show();

    return true;
}

Game::Game() {
    isRunning = true;
    MyInterface = nullptr;
    menuScreen = nullptr;

    textFPS = nullptr;

   
}

Game::~Game() {
    TTF_Quit();
    // SDL_StopTextInput();

    delete MyInterface;
    MyInterface = nullptr;

    delete menuScreen;
    menuScreen = nullptr;
}



void Game::Run() {
    int i, currentFPS = 0, mouseX, mouseY;
    SDL_Event event;
    stack <Interface*> mystack;
    stack <bool> canRender;
    bool checked[MAX_INTERFACE_ELEMENTS];
    bool b_canRender = true;
    bool KEYS[322];
    unsigned int lastRenderTime = 0,
                 currentRenderTime,
                 renderInterval = 1000 / MAX_FPS,
                 tmpTime = SDL_GetTicks();

    memset(KEYS, 0, sizeof(bool) * 322);

    while (MyInterface->CheckIfRunning() && isRunning) {
        while (SDL_PollEvent(&event)) {
            /* We are only worried about SDL_KEYDOWN and SDL_KEYUP events */
            switch (event.type) {
            case SDL_KEYDOWN:
                printf("Key press detected\n");
                KEYS[event.key.keysym.sym] = true;
                for (auto it : MyInterface->uiElements) {
                    it->OnKeyPress(KEYS, event.key.keysym.sym);
                }
                break;

            case SDL_KEYUP:
                printf("Key release detected\n");
                KEYS[event.key.keysym.sym] = false;
                for (auto it : MyInterface->uiElements) {
                    it->OnKeyRelease(event.key.keysym.sym);
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                printf("Mouse click detected\n");
                SDL_GetMouseState(&mouseX, &mouseY);
                for (auto it : MyInterface->uiElements) {
                    it->OnMouseClick(event.button, mouseX, mouseY);
                }
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
        for (auto it : MyInterface->uiElements) {
            
            if (it->GetParent() == nullptr) {
                it->CheckPressedKeys();
                it->Update();
                if(it->isShow() && b_canRender)
                    it->Render();

                checked[i] = true;

                //Verific daca e parinte si ii caut toti copiii
                if (it->isParent()) {
                    mystack.push(it);
                    canRender.push(it->isShow());

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
