#include <iostream>
#include <stack>
#include <chrono>
#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <fstream>

#include "Game.h"
#include "config.h"

using namespace std;

Game::Game() {
    isRunning = true;

    MyInterface = nullptr;
    textFPS = nullptr;
    titleImage = nullptr;

    gameMenu = nullptr;
    gameMap = nullptr;
    gameSettings = nullptr;
    backButton = nullptr;

    resolutionX = 800;
    resolutionY = 600;
}

Game::~Game() {

    if (nullptr != textFPS)
        delete textFPS;

    if (nullptr != titleImage)
        delete titleImage;

    if (nullptr != gameMenu)
        delete gameMenu;

    if (nullptr != gameMap)
        delete gameMap;

    if (nullptr != gameSettings)
        delete gameSettings;

    if (nullptr != backButton)
        delete backButton;

    if (nullptr != MyInterface)
        delete MyInterface;
}

bool Game::Init() {
    

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        CHECK_ERROR(false, "SDL-ul nu s-a putut initializa", SDL_GetError(), __LINE__, __FILE__);
    }

    int resolutionX, resolutionY;
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    ifstream IN("game.config", ifstream::in);
    IN >> resolutionX >> resolutionY;

    if (resolutionX > DM.w || resolutionY > DM.h) {
        resolutionX = DM.w;
        resolutionY = DM.h;
    }

    Interface::Window = SDL_CreateWindow("Retro Hub",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        resolutionX,
        resolutionY,
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
    gameMenu->SetStartButtonEvent(bind(&Game::StartEvent, this));
    gameMenu->SetSettingsButtonEvent(bind(&Game::SettingsEvent, this));
    gameMenu->SetHelpButtonEvent(bind(&Game::ExitEvent, this));
    gameMenu->SetExitButtonEvent(bind(&Game::ExitEvent, this));
    gameMenu->Show();

    gameMap = new Map;
    CHECK(gameMap->Init(), "gameMap->Init()", __LINE__, __FILE__);
    gameMap->Hide();

    backButton = new MenuButton();
    CHECK(backButton->Init("Inapoi la meniu", 25), "backButton->Init()", __LINE__, __FILE__);
    //backButton->Init("Inapoi la meniu", 25);
    backButton->SetPosition(Interface::GetWindowSize().x - 170, 20);
    backButton->SetLeftClickEvent(bind(&Game::BackToMenuEvent, this));
    backButton->Show();

    gameSettings = new Settings;
    CHECK(gameSettings->Init(), "gameMap->Init()", __LINE__, __FILE__);
    gameSettings->Hide();
    StartEvent();


    textFPS = new TextLine;
    CHECK(textFPS->SetFont("assets/font/NerkoOne-Regular.ttf", 20), "textFPS->SetFont()", __LINE__, __FILE__);
    CHECK(textFPS->SetColor(255, 255, 255), "textFPS->SetColor()", __LINE__, __FILE__);
    CHECK(textFPS->SetText("FPS: 0"), "textFPS->SetText()", __LINE__, __FILE__);
    //textFPS->SetFont("assets/font/NerkoOne-Regular.ttf", 20);
    //textFPS->SetColor(255, 255, 255);
    //textFPS->SetText("FPS: 0");
    textFPS->SetPosition(10, 5);
    textFPS->Show();

    srand(static_cast<unsigned int>(time(NULL)));

    return true;
}

void Game::StartEvent() {
    gameMenu->Hide();
    gameMap->ShowMap();
    backButton->BringToFront();
    backButton->Show();
}


void Game::SettingsEvent() {
    gameMenu->Hide();
    gameSettings->ShowSettings();
    backButton->BringToFront();
    backButton->Show();
}

void Game::ExitEvent() {
    isRunning = false;
}

void Game::BackToMenuEvent() {
    gameMenu->Show();
    gameMap->HideMap();
    gameSettings->Hide();
    backButton->Hide();
}

void Game::Run() {
    //std::map<int, bool>;
    int x = 0;
    int i, currentFPS = 0;
    SDL_Event event;
    stack <Interface*> mystack;
    stack <bool> canRender;
    bool checked[MAX_INTERFACE_ELEMENTS];
    bool b_canRender = true;
    bool KEYS[SDL_NUM_SCANCODES];
    unsigned int lastRenderTime = 0,
                 currentRenderTime,
                 renderInterval = 1000 / MAX_FPS,
                 tmpTime = SDL_GetTicks(); //Update text fps la fiecare secunda
    char tmpBuffer[10];

    memset(KEYS, 0, sizeof(bool) * SDL_NUM_SCANCODES);

    auto interfaceBegin = MyInterface->uiElements.begin();
   
    while (MyInterface->CheckIfRunning() && isRunning) {
        //Check self-destroy event
        for (i = 0; i < MyInterface->uiElements.size(); ++i) {
            if (MyInterface->uiElements.begin()[i]->IsSelfDestroy()) {
                delete MyInterface->uiElements.begin()[i];
                MyInterface->uiElements.erase(MyInterface->uiElements.begin() + i);
                --i;
            }
        }



        SDL_GetMouseState(&Interface::mouseX, &Interface::mouseY);
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_KEYDOWN:
                //printf("Key press detected: %d\n", event.key.keysym.sym);
                if (event.key.keysym.scancode < SDL_NUM_SCANCODES && event.key.keysym.scancode >= 0) {
                    KEYS[event.key.keysym.scancode] = true;
                    for (i = 0; i < MyInterface->uiElements.size(); ++i) {
                        if(MyInterface->uiElements.begin()[i]->isShow())
                            MyInterface->uiElements.begin()[i]->OnKeyPress(KEYS, event.key.keysym.scancode);
                    }
                }
                break;

            case SDL_KEYUP:
                //printf("Key release detected: %d\n", event.key.keysym.sym);
                if (event.key.keysym.scancode < SDL_NUM_SCANCODES && event.key.keysym.scancode >= 0) {
                    KEYS[event.key.keysym.scancode] = false;
                    for (i = 0; i < MyInterface->uiElements.size(); ++i) {
                        if (MyInterface->uiElements.begin()[i]->isShow())
                            MyInterface->uiElements.begin()[i]->OnKeyRelease(KEYS, event.key.keysym.scancode);
                    }
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                /*
                * Verific toate elementele interfetei si apelez evenimentul
                * de click pe elementul cel mai din fata
                */
                for (int64_t j = MyInterface->uiElements.size() - 1; j >= 0; --j) { // TODO: Posibil segmentation fault daca in OnMouseClick se mai sterg elemente
                    if (MyInterface->uiElements.begin()[j]->isRealShow() && MyInterface->uiElements.begin()[j]->IsOnMouseRange()) {
                        if (MyInterface->uiElements.begin()[j]->isParent()) {
                            if (!MyInterface->uiElements.begin()[j]->CheckLeftClick(event.button))
                                MyInterface->uiElements.begin()[j]->OnMouseClick(event.button);
                            MyInterface->uiElements.begin()[j]->SetCursorFollwing(true);
                            if(MyInterface->uiElements.begin()[j]->IsMovable())
                                MyInterface->uiElements.begin()[j]->BringToFront();
                            break;

                        }
                        else {
                            MyInterface->uiElements.begin()[j]->OnMouseClick(event.button);
                            if (!MyInterface->uiElements.begin()[j]->GetParent()) { // Daca nu are parinti, testez daca se poate misca
                                MyInterface->uiElements.begin()[j]->SetCursorFollwing(true);
                                if (MyInterface->uiElements.begin()[j]->IsMovable())
                                    MyInterface->uiElements.begin()[j]->BringToFront();
                            }
                            break;
                        }
                    }
                }

                break;

            case SDL_MOUSEBUTTONUP:
                //printf("Mouse release detected\n");
                for (i = 0; i < MyInterface->uiElements.size(); ++i) {
                    MyInterface->uiElements.begin()[i]->SetCursorFollwing(false);
                    MyInterface->uiElements.begin()[i]->OnMouseRelease();
                }

                break;

            case SDL_QUIT:
                isRunning = false;

            default:
                break;
            }
        }

        if (FPS_LIMIT_ENABLED) {
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

        // TODO: Randarea separatata de update -> mult mai rapid

        i = 0;
        int64_t interfaceSize = MyInterface->uiElements.size();
        
        for (int it = 0; it < interfaceSize; ++it) {
            
            if (MyInterface->uiElements.begin()[it]->GetParent() == nullptr) {
                MyInterface->uiElements.begin()[it]->UpdateFollowingPosition();
                MyInterface->uiElements.begin()[it]->CheckPressedKeys();
                MyInterface->uiElements.begin()[it]->Update();
                if (MyInterface->uiElements.begin()[it]->isShow() && b_canRender) {
                    MyInterface->uiElements.begin()[it]->VerifyMouseState();
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

                                MyInterface->uiElements.begin()[j]->UpdateFollowingPosition();
                                MyInterface->uiElements.begin()[j]->CheckPressedKeys();
                                MyInterface->uiElements.begin()[j]->Update();
                                MyInterface->uiElements.begin()[j]->UpdatePosition();

                                //Daca nu are parinti, verific daca el este vizibil
                                if (canRender.top() && MyInterface->uiElements.begin()[j]->isShow() && b_canRender) {
                                    MyInterface->uiElements.begin()[j]->VerifyMouseState();
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
	}
}
