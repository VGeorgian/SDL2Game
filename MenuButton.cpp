#include <iostream>
#include "MenuButton.h"

MenuButton::MenuButton() {
    text = nullptr;
    blueText = nullptr;
    redText = nullptr;
}


MenuButton::~MenuButton() {
    if(nullptr != text)
	    delete text;

    if(nullptr != blueText)
        delete blueText;

    if (nullptr != redText)
        delete redText;
}

bool MenuButton::Init(const char* titlu, int fontSize) {
    blueText = new TextLine;
    blueText->SetFont("assets/font/Bangers-Regular.ttf", fontSize);
    blueText->SetParent(this);
    blueText->SetColor(0, 0, 255);
    blueText->SetText(titlu);
    blueText->SetPosition(0, 0);
    blueText->Show();

    redText = new TextLine;
    redText->SetFont("assets/font/Bangers-Regular.ttf", fontSize);
    redText->SetParent(this);
    redText->SetColor(255, 0, 0);
    redText->SetText(titlu);
    redText->SetPosition(0, 0);
    redText->Show();


    text = new TextLine;
    text->SetFont("assets/font/Bangers-Regular.ttf", fontSize);
    text->SetParent(this);
    text->SetColor(255, 255, 255);
    text->SetText(titlu);
    text->SetPosition(0, 0);
    text->Show();

    int w, h;
    TTF_SizeText(text->GetFont(), titlu, &w, &h);
    this->SetSize(w, h);

    return true;
}

void MenuButton::OnMouseIn() {
    blueText->SetPosition(-5, -5);
    redText->SetPosition(5, 5);
}

void MenuButton::OnMouseOut() {
    blueText->SetPosition(0, 0);
    redText->SetPosition(0, 0);
}

void MenuButton::SetLeftClickEvent(function<void(void)> callback_func) {
    this->callback = callback_func;
    if (nullptr != text) {
        blueText->SetLeftClickEvent(callback_func);
        redText->SetLeftClickEvent(callback_func);
        text->SetLeftClickEvent(callback_func);
    }

}