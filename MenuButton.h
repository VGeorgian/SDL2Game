#pragma once
#include "SDL.h"
#include "config.h"
#include "Interface.h"
#include "TextLine.h"

using namespace std;

class MenuButton : public Interface {

protected:
    TextLine* text;
    TextLine* blueText;
    TextLine* redText;
public:
    MenuButton(const char* titlu, int fontSize = 40);
    ~MenuButton();

    //bool LoadImage(const char path[]);
    //void Render();
    void SetLeftClickEvent(function<void(void)> callback_func);
    void OnMouseIn();
    void OnMouseOut();

};