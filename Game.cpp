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
    isRunning = true;

    MyInterface = nullptr;
    menuScreen = nullptr;
    board = nullptr;
    board2 = nullptr;

    boardText = nullptr;
    boardText2 = nullptr;
    textFPS = nullptr;
}

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


    MyInterface = new Interface(true);

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

    board2 = new Image;
    CHECK(board2->LoadImage("assets/img/board.png"), "board->LoadImage()", __LINE__, __FILE__);
    board2->SetPosition(10, 50);
    board2->SetSize(500, 500);
    board2->SetFocus();
    board2->AddMovableTag();
    board2->Show();

    board = new Image;
    CHECK(board->LoadImage("assets/img/board.png"), "board->LoadImage()", __LINE__, __FILE__);
    board->SetPosition(300, 10);
    board->SetSize(500, 500);
    board->SetFocus();
    board->AddMovableTag();
    board->SetHorizontalCenterPosition();
    board->Show();

    board3 = new Image;
    board3->SetParent(board);
    CHECK(board3->LoadImage("assets/img/board.png"), "board->LoadImage()", __LINE__, __FILE__);
    board3->SetPosition(200, 200);
    board3->SetSize(500, 500);
    board3->Show();

    boardText2 = new TextLine;
    boardText2->SetParent(board2);
    boardText2->SetFont("assets/font/NerkoOne-Regular.ttf", 40);
    boardText2->SetColor(255, 255, 255);
    boardText2->SetText("Board2");
    boardText2->SetPosition(100, 200);
    boardText2->SetHorizontalCenterPosition();
    boardText2->Show();

    boardText = new TextLine;
    boardText->SetParent(board3);
    boardText->SetFont("assets/font/NerkoOne-Regular.ttf", 40);
    boardText->SetColor(255, 255, 255);
    boardText->SetText("Board1");
    boardText->SetPosition(0, 0);
    boardText->SetHorizontalCenterPosition();
    boardText->Show();


    return true;
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

    auto interfaceBegin = MyInterface->uiElements.begin();

    while (MyInterface->CheckIfRunning() && isRunning) {
        SDL_GetMouseState(&mouseX, &mouseY);
        while (SDL_PollEvent(&event)) {
            /* We are only worried about SDL_KEYDOWN and SDL_KEYUP events */
            switch (event.type) {
            case SDL_KEYDOWN:
                printf("Key press detected: %d\n", event.key.keysym.sym);
                if (event.key.keysym.sym < KEYS_NUMBER) {
                    KEYS[event.key.keysym.sym] = true;
                    for (auto it : MyInterface->uiElements) {
                        it->OnKeyPress(KEYS, event.key.keysym.sym);
                    }
                }
                break;

            case SDL_KEYUP:
                printf("Key release detected: %d\n", event.key.keysym.sym);
                if (event.key.keysym.sym < KEYS_NUMBER) {
                    KEYS[event.key.keysym.sym] = false;
                    for (auto it : MyInterface->uiElements) {
                        it->OnKeyRelease(event.key.keysym.sym);
                    }
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                printf("Mouse click detected\n");
                pos = -1;
                i = -1;
                for (auto it : MyInterface->uiElements) {
                    ++i;
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
                    tmpInterface = interfaceBegin[pos];

                    i = 1;
                    for (auto it : MyInterface->uiElements) {
                        if (it->GetParent() == interfaceBegin[pos] && it->CheckFocus(mouseX, mouseY)) {
                            i = 0;
                            break;
                        }
                    }

                    if(i)
                        interfaceBegin[pos]->SetCursorFollwing(true, mouseX, mouseY);
                    MyInterface->uiElements.erase(interfaceBegin + pos);
                    MyInterface->uiElements.push_back(tmpInterface);
                }

                break;

            case SDL_MOUSEBUTTONUP:
                printf("Mouse release detected\n");
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

        for (auto it : MyInterface->uiElements) {
            
            if (it->GetParent() == nullptr) {
                it->UpdateFollowingPosition(mouseX, mouseY);
                it->CheckPressedKeys();
                it->Update();
                if (it->isShow() && b_canRender) {
                    it->Render();
                }

                checked[i] = true;

                //Verific daca e parinte si ii caut toti copiii
                if (it->isParent()) {
                    mystack.push(it);
                    canRender.push(it->isShow());

                    for (int j = 0; j < MyInterface->uiElements.size(); ++j) {
                        if (!checked[j]) {
                            if (!mystack.empty() && interfaceBegin[j]->GetParent() == mystack.top()) {

                                //Verific daca parintii lui sunt afisati
                                if (interfaceBegin[j]->isParent()) {
                                    if (canRender.top())
                                        canRender.push(interfaceBegin[j]->isShow());
                                    else
                                        canRender.push(false);
                                }

                                interfaceBegin[j]->UpdateFollowingPosition(mouseX, mouseY);
                                interfaceBegin[j]->CheckPressedKeys();
                                interfaceBegin[j]->Update();
                                interfaceBegin[j]->UpdatePosition();

                                //Daca nu are parinti, verific daca el este vizibil
                                if(canRender.top() && interfaceBegin[j]->isShow() && b_canRender)
                                    interfaceBegin[j]->Render();

                                checked[j] = true;

                                if (interfaceBegin[j]->isParent()) {
                                    mystack.push(interfaceBegin[j]);
                                    cout << "Am gasit parinte:\n";
                                    j = -1;
                                }

                                //Daca s-a ajuns la ultimul element si stiva mai 
                                //are elemente, elimin ultimul element
                                /*else if (j == MyInterface->uiElements.size() - 1) {
                                    mystack.pop();
                                    canRender.pop();
                                    j = -1;
                                }*/
                            }
                        }
                        if ((j == MyInterface->uiElements.size() - 1) && !mystack.empty()) {
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
