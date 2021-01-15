#include <iostream>
#include "Settings.h"

using namespace std;

Settings::Settings() {
	title = nullptr;
	backButton = nullptr;
	screenSizeLabel = nullptr;
	musicStatusLabel = nullptr;
}

Settings::~Settings() {
	if (nullptr != title)
		delete title;

	if (nullptr != backButton)
		delete backButton;

	if (nullptr != screenSizeLabel)
		delete screenSizeLabel;

	if (nullptr != musicStatusLabel)
		delete musicStatusLabel;
}

bool Settings :: Init() {
	this->LoadImage("assets/img/background_menu.jpg");
	this->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	this->Show();

	title = new TextLine();
	title->SetParent(this);
	title->SetFont("assets/font/Bangers-Regular.ttf", 50);
	title->SetColor(255, 255, 255);
	title->SetText("SETARI");
	title->SetPosition(30, 60);
	title->Show();

	backButton = new MenuButton("SALVEAZÃ SETARI", 60);
	backButton->SetPosition(30, SCREEN_HEIGHT - 100);
	backButton->SetParent(this);
	//backButton->SetHorizontalCenterPosition();
	//backButton->SetLeftClickEvent(bind(&Snake::StartGame, this));
	backButton->Show();

	saveButton = new MenuButton("Inapoi la meniu", 25);
	saveButton->SetPosition(SCREEN_WIDTH - 170, 20);
	saveButton->SetParent(this);
	//saveButton->SetHorizontalCenterPosition();
	//saveButton->SetLeftClickEvent(bind(&Snake::StartGame, this));
	saveButton->Show();

	screenSizeLabel = new TextLine();
	screenSizeLabel->SetParent(this);
	screenSizeLabel->SetFont("assets/font/Bangers-Regular.ttf", 30);
	screenSizeLabel->SetColor(255, 255, 255);
	screenSizeLabel->SetText("REZOLUTIE JOC");
	screenSizeLabel->SetPosition(60, 180);
	screenSizeLabel->Show();

	musicStatusLabel = new TextLine();
	musicStatusLabel->SetParent(this);
	musicStatusLabel->SetFont("assets/font/Bangers-Regular.ttf", 30);
	musicStatusLabel->SetColor(255, 255, 255);
	musicStatusLabel->SetText("MUZICA FUNDAL");
	musicStatusLabel->SetPosition(60, 230);
	musicStatusLabel->Show();

	volumeLabel = new TextLine();
	volumeLabel->SetParent(this);
	volumeLabel->SetFont("assets/font/Bangers-Regular.ttf", 30);
	volumeLabel->SetColor(255, 255, 255);
	volumeLabel->SetText("VOLUM");
	volumeLabel->SetPosition(60, 280);
	volumeLabel->Show();



	return true;
}