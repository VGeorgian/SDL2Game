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
    blueText->SetParent(this);
    CHECK(blueText->SetFont("assets/font/Bangers-Regular.ttf", fontSize), "blueText->SetFont()", __LINE__, __FILE__);
    CHECK(blueText->SetColor(0, 0, 255), "blueText->SetColor()", __LINE__, __FILE__);
    CHECK(blueText->SetText(titlu), "blueText->SetText()", __LINE__, __FILE__);
    //blueText->SetFont("assets/font/Bangers-Regular.ttf", fontSize);
    //blueText->SetColor(0, 0, 255);
    //blueText->SetText(titlu);
    blueText->SetPosition(0, 0);
    blueText->Show();

    redText = new TextLine;
    redText->SetParent(this);
    CHECK(redText->SetFont("assets/font/Bangers-Regular.ttf", fontSize), "redText->SetFont()", __LINE__, __FILE__);
    CHECK(redText->SetColor(255, 0, 0), "redText->SetColor()", __LINE__, __FILE__);
    CHECK(redText->SetText(titlu), "redText->SetText()", __LINE__, __FILE__);
    //redText->SetFont("assets/font/Bangers-Regular.ttf", fontSize);
    //redText->SetColor(255, 0, 0);
    //redText->SetText(titlu);
    redText->SetPosition(0, 0);
    redText->Show();


    text = new TextLine;
    text->SetParent(this);
    CHECK(text->SetFont("assets/font/Bangers-Regular.ttf", fontSize), "text->SetFont()", __LINE__, __FILE__);
    CHECK(text->SetColor(255, 255, 255), "text->SetColor()", __LINE__, __FILE__);
    CHECK(text->SetText(titlu), "text->SetText()", __LINE__, __FILE__);
    //text->SetFont("assets/font/Bangers-Regular.ttf", fontSize);
    //text->SetColor(255, 255, 255);
    //text->SetText(titlu);
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