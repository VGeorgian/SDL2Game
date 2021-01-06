#include <iostream>
#include "MenuButton.h"

MenuButton::MenuButton(const char* titlu) {
    blueText = new TextLine;
    blueText->SetFont("assets/font/Bangers-Regular.ttf", 40);
    blueText->SetParent(this);
    blueText->SetColor(0, 0, 255);
    blueText->SetText(titlu);
    blueText->SetPosition(0, 0);
    blueText->Show();

    redText = new TextLine;
    redText->SetFont("assets/font/Bangers-Regular.ttf", 40);
    redText->SetParent(this);
    redText->SetColor(255, 0, 0);
    redText->SetText(titlu);
    redText->SetPosition(0, 0);
    redText->Show();


	text = new TextLine;
    text->SetFont("assets/font/Bangers-Regular.ttf", 40);
    text->SetParent(this);
    text->SetColor(255, 255, 255);
    text->SetText(titlu);
    text->SetPosition(0, 0);
    text->Show();

    int w, h;
    TTF_SizeText(text->GetFont(), titlu, &w, &h);
    this->SetSize(w, h);

}

MenuButton::~MenuButton() {
	delete text;
}

void MenuButton::OnMouseIn() {
    blueText->SetPosition(-5, -5);
    redText->SetPosition(5, 5);
}

void MenuButton::OnMouseOut() {
    blueText->SetPosition(0, 0);
    redText->SetPosition(0, 0);
}