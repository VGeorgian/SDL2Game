#pragma once
#include <functional>
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
    std::function<void(void)> callback;
public:
    MenuButton(const char* titlu);
    ~MenuButton();

    //bool LoadImage(const char path[]);
    //void Render();

    void OnMouseIn();
    void OnMouseOut();
    void OnLeftClick(const int& x, const int& y);
    void SetLeftClickEvent(function<void(void)> callback_func);

};