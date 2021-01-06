#include <iostream>
#include <stack>
#include <chrono>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Game.h"
#include "config.h"

using namespace std;

Game::Game() {
    isRunning = true;

    MyInterface = nullptr;
    titleImage = nullptr;

    gameMenu = nullptr;
    gameMap = nullptr;

    textFPS = nullptr;
}

bool Game::Init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        CHECK_ERROR(false, "SDL-ul nu s-a putut initializa", SDL_GetError(), __LINE__, __FILE__);
    }

    Interface::Window = SDL_CreateWindow("Retro Hub",
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

    MyInterface = new Interface(true);

    gameMenu = new Menu;
    CHECK(gameMenu->Init(), "gameMenu->Init()", __LINE__, __FILE__);
    gameMenu->startButton->SetLeftClickEvent(bind(&Game::StartEvent, this));
    gameMenu->exitButton->SetLeftClickEvent(bind(&Game::ExitEvent, this));
    //gameMenu->Show();

    gameMap = new Map;
    CHECK(gameMap->Init(), "gameMap->Init()", __LINE__, __FILE__);
    //gameMap->Hide();

    textFPS = new TextLine;
    textFPS->SetFont("assets/font/NerkoOne-Regular.ttf", 20);
    textFPS->SetColor(255, 255, 255);
    textFPS->SetText("FPS: 0");
    textFPS->SetPosition(10, 5);
    textFPS->Show();

    return true;
}

Game::~Game() {

    if(nullptr != MyInterface)
        delete MyInterface;

    if (nullptr != gameMenu)
       delete gameMenu;

    if (nullptr != gameMap)
        delete gameMap;


    if (nullptr != textFPS)
        delete textFPS;

    TTF_Quit();
}

void Game::StartEvent() {
    gameMenu->Hide();
}

void Game::ExitEvent() {
    isRunning = false;
}

void Game::Run() {
    int x = 0;
    int i, currentFPS = 0, mouseX, mouseY, pos;
    SDL_Event event;
    stack <Interface*> mystack;
    stack <bool> canRender;
    bool checked[MAX_INTERFACE_ELEMENTS];
    bool b_canRender = true;
    bool KEYS[KEYS_NUMBER];
    unsigned int lastRenderTime = 0,
                 currentRenderTime,
                 renderInterval = 1000 / MAX_FPS,
                 tmpTime = SDL_GetTicks(); //Update text fps la fiecare secunda

    Interface* tmpInterface;
    char tmpBuffer[10];

    memset(KEYS, 0, sizeof(bool) * KEYS_NUMBER);

    //auto interfaceBegin = MyInterface->uiElements.begin();

    using namespace std::chrono;
    milliseconds ms = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
        );
    cout << ms.count() << endl;
   
    while (MyInterface->CheckIfRunning() && isRunning) {
        SDL_GetMouseState(&mouseX, &mouseY);
        while (SDL_PollEvent(&event)) {

            switch (event.type) {
            case SDL_KEYDOWN:
                //printf("Key press detected: %d\n", event.key.keysym.sym);
                if (event.key.keysym.sym < KEYS_NUMBER) {
                    KEYS[event.key.keysym.sym] = true;
                    for (auto it : MyInterface->uiElements) {
                        if(it->isShow())
                            it->OnKeyPress(KEYS, event.key.keysym.sym);
                    }
                }
                break;

            case SDL_KEYUP:
                //printf("Key release detected: %d\n", event.key.keysym.sym);
                if (event.key.keysym.sym < KEYS_NUMBER) {
                    KEYS[event.key.keysym.sym] = false;
                    for (auto it : MyInterface->uiElements) {
                        if (it->isShow())
                            it->OnKeyRelease(KEYS, event.key.keysym.sym);
                    }
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                //printf("Mouse click detected\n");
                pos = -1;
                i = -1;
                for (auto it : MyInterface->uiElements) {
                    ++i;
                    if (it->isRealShow()) // 
                        it->OnMouseClick(event.button, mouseX, mouseY);
                    //it->FollowCursor(event.button, mouseX, mouseY);
                    if (it->CheckFocus(mouseX, mouseY)) {
                        if (it->IsFocusable())
                            pos = i;
                        else
                            pos = -1;
                    }
                }

                if (pos != -1) {
                    tmpInterface = MyInterface->uiElements.begin()[pos];

                    i = 1;
                    for (auto it : MyInterface->uiElements) {
                        if (it->GetParent() == MyInterface->uiElements.begin()[pos] && it->CheckFocus(mouseX, mouseY)) {
                            i = 0;
                            break;
                        }
                    }

                    if(i)
                        MyInterface->uiElements.begin()[pos]->SetCursorFollwing(true, mouseX, mouseY);
                    MyInterface->uiElements.erase(MyInterface->uiElements.begin() + pos);
                    MyInterface->uiElements.push_back(tmpInterface);
                }

                break;

            case SDL_MOUSEBUTTONUP:
                //printf("Mouse release detected\n");
                for (auto it : MyInterface->uiElements) {
                    it->SetCursorFollwing(false);
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
        int interfaceSize = MyInterface->uiElements.size();
        
        for (int it = 0; it < interfaceSize; ++it) {
            
            if (MyInterface->uiElements.begin()[it]->GetParent() == nullptr) {
                MyInterface->uiElements.begin()[it]->UpdateFollowingPosition(mouseX, mouseY);
                MyInterface->uiElements.begin()[it]->CheckPressedKeys();
                MyInterface->uiElements.begin()[it]->Update();
                if (MyInterface->uiElements.begin()[it]->isShow() && b_canRender) {
                    MyInterface->uiElements.begin()[it]->VerifyMouseState(mouseX, mouseY);
                    MyInterface->uiElements.begin()[it]->Render();
                }

                checked[i] = true;

                //Verific daca e parinte si ii caut toti copiii
                if (MyInterface->uiElements.begin()[it]->isParent()) {
                    mystack.push(MyInterface->uiElements.begin()[it]);
                    canRender.push(MyInterface->uiElements.begin()[it]->isShow());

                    for (int j = 0; j < interfaceSize; ++j) {
                        if (!checked[j]) {
                            if (!mystack.empty() && MyInterface->uiElements.begin()[j]->GetParent() == mystack.top()) {

                                //Verific daca parintii lui sunt afisati
                                if (MyInterface->uiElements.begin()[j]->isParent()) {
                                    if (canRender.top())
                                        canRender.push(MyInterface->uiElements.begin()[j]->isShow());
                                    else
                                        canRender.push(false);
                                }

                                MyInterface->uiElements.begin()[j]->UpdateFollowingPosition(mouseX, mouseY);
                                MyInterface->uiElements.begin()[j]->CheckPressedKeys();
                                MyInterface->uiElements.begin()[j]->Update();
                                MyInterface->uiElements.begin()[j]->UpdatePosition();

                                //Daca nu are parinti, verific daca el este vizibil
                                if (canRender.top() && MyInterface->uiElements.begin()[j]->isShow() && b_canRender) {
                                    MyInterface->uiElements.begin()[j]->VerifyMouseState(mouseX, mouseY);
                                    MyInterface->uiElements.begin()[j]->Render();
                                }

                                checked[j] = true;

                                if (MyInterface->uiElements.begin()[j]->isParent()) {
                                    mystack.push(MyInterface->uiElements.begin()[j]);
                                    j = -1;
                                }
                            }
                        }
                        if ((j == interfaceSize - 1) && !mystack.empty()) {
                            mystack.pop();
                            canRender.pop();
                            j = -1;
                        }
                    }
                }
            }
            ++i;
        }

        if (b_canRender)
            SDL_RenderPresent(Interface::renderer);

        //SDL_Delay(1000);
	}
}
