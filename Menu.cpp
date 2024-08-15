#include "Menu.h"

Menu::Menu() {
    titleImage = nullptr;
	startButton = nullptr;
    settingsButton = nullptr;
	helpButton = nullptr;
	exitButton = nullptr;
}

Menu::~Menu() {
    if (nullptr != titleImage)
        delete titleImage;

	if (nullptr != startButton)
		delete startButton;

	if (nullptr != settingsButton)
		delete settingsButton;

	if (nullptr != helpButton)
		delete helpButton;

	if (nullptr != exitButton)
		delete exitButton;
}

bool Menu::Init() {
    CHECK(this->LoadImage("assets/img/background_menu.jpg"), "menuScreen->LoadImage()", __LINE__, __FILE__);
    this->SetPosition(0, 0);
    this->SetSize(GetWindowSize().x, GetWindowSize().y);
    //this->Show();

    titleImage = new Image;
    CHECK(titleImage->LoadImage("assets/img/menu-title.png"), "titleImage->LoadImage()", __LINE__, __FILE__);
    titleImage->SetParent(this);
    titleImage->SetPosition(40, 50);
    titleImage->SetSize(358, 98);
    titleImage->Show();

    startButton = new MenuButton;
    CHECK(startButton->Init("START"), "startButton->Init()", __LINE__, __FILE__);
    //startButton->Init("START");
    startButton->SetParent(this);
    startButton->SetPosition(60, 250);
    startButton->Show();

    settingsButton = new MenuButton();
    CHECK(settingsButton->Init("SETARI"), "settingsButton->Init", __LINE__, __FILE__);
    //settingsButton->Init("SETARI");
    settingsButton->SetParent(this);
    settingsButton->SetPosition(60, 295);
    settingsButton->Show();

    helpButton = new MenuButton();
    CHECK(helpButton->Init("CUM SE JOACA?"), "helpButton->Init", __LINE__, __FILE__);
    //helpButton->Init("CUM SE JOACA?");
    helpButton->SetParent(this);
    helpButton->SetPosition(60, 340);
    helpButton->Show();

    exitButton = new MenuButton();
    CHECK(exitButton->Init("IESIRE"), "exitButton->Init", __LINE__, __FILE__);
    //exitButton->Init("IESIRE");
    exitButton->SetParent(this);
    exitButton->SetPosition(60, 385);
    exitButton->Show();

	return true;
}

void Menu::SetStartButtonEvent(function<void(void)> callback_func) {
    startButton->SetLeftClickEvent(callback_func);
}
void Menu::SetSettingsButtonEvent(function<void(void)> callback_func) {
    settingsButton->SetLeftClickEvent(callback_func);
}
void Menu::SetHelpButtonEvent(function<void(void)> callback_func) {
    helpButton->SetLeftClickEvent(callback_func);
}
void Menu::SetExitButtonEvent(function<void(void)> callback_func) {
    exitButton->SetLeftClickEvent(callback_func);
}