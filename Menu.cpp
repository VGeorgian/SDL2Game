#include "Menu.h"

Menu::Menu() {
    titleImage = nullptr;
	startButton = nullptr;
	optionButton = nullptr;
	helpButton = nullptr;
	exitButton = nullptr;
}

Menu::~Menu() {
    if (nullptr != titleImage)
        delete titleImage;

	if (nullptr != startButton)
		delete startButton;

	if (nullptr != optionButton)
		delete optionButton;

	if (nullptr != helpButton)
		delete helpButton;

	if (nullptr != exitButton)
		delete exitButton;
}

bool Menu::Init() {
    CHECK(this->LoadImage("assets/img/background_menu.jpg"), "menuScreen->LoadImage()", __LINE__, __FILE__);
    this->SetPosition(0, 0);
    this->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    //this->Show();

    titleImage = new Image;
    CHECK(titleImage->LoadImage("assets/img/menu-title.png"), "titleImage->LoadImage()", __LINE__, __FILE__);
    titleImage->SetParent(this);
    titleImage->SetPosition(40, 50);
    titleImage->SetSize(358, 98);
    titleImage->Show();

    startButton = new MenuButton("START");
    startButton->SetParent(this);
    startButton->SetPosition(60, 250);
    //startButton->SetLeftClickEvent(bind(&Game::StartEvent, this));
    startButton->Show();

    optionButton = new MenuButton("SETARI");
    optionButton->SetParent(this);
    optionButton->SetPosition(60, 295);
    optionButton->Show();

    helpButton = new MenuButton("CUM SE JOACA?");
    helpButton->SetParent(this);
    helpButton->SetPosition(60, 340);
    helpButton->Show();

    exitButton = new MenuButton("IESIRE");
    exitButton->SetParent(this);
    exitButton->SetPosition(60, 385);
   // helpButton->SetLeftClickEvent(bind(&Game::ExitEvent, this));
    exitButton->Show();

	return true;
}