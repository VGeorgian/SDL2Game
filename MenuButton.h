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
    MenuButton(const char* titlu);
    ~MenuButton();

    //bool LoadImage(const char path[]);
    //void Render();

    void OnMouseIn();
    void OnMouseOut();

};