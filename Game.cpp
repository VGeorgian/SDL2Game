#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <stack>

#include "Game.h"
#include "Image.h"
#include "config.h"

using namespace std;

Game::Game() {
    background = nullptr;
    background2 = nullptr;
    background3 = nullptr;
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
            Init();
        }

    }
}

Game::~Game() {
	delete MyInterface;
}

void Game::Init() {
    background = new Image;
    background->LoadImage("robi.png");
    background->SetPosition(50, 50);
    background->SetSize(100, 100);

    background2 = new Image;
    background2->SetParent(background);
    background2->LoadImage("robi.png");
    background2->SetPosition(90, 10);
    background2->SetSize(80, 80);

    background3 = new Image;
    background3->SetParent(background2);
    background3->LoadImage("robi.png");
    background3->SetPosition(20, 20);
    background3->SetSize(40, 40);

    background->Show();
    background2->Show();
}
void Game::Run() {
    int x = 0, i;
    SDL_Event event;
    stack <Interface*> mystack;
    stack <bool> canRender;
    bool checked[MAX_INTERFACE_ELEMENTS];

	while (MyInterface->CheckIfRunning()) {
        SDL_PollEvent(&event);
       background->SetPosition(x++, 10);
       SDL_Delay(100);

        SDL_RenderClear(Interface::renderer);

        for (i = 0; i < MyInterface->uiElements.size(); ++i) {
            checked[i] = false;
        }

        i = 0;
        for (vector<Interface*>::iterator it = MyInterface->uiElements.begin(); it != MyInterface->uiElements.end(); ++it) {
            
            if ((*it)->GetParent() == nullptr) {
                (*it)->CheckPressedKeys();
                (*it)->Update();
                if((*it)->isShow())
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

        SDL_RenderPresent(Interface::renderer);

	}
}
