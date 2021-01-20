#include <iostream>
#include "Dropdown.h"
using namespace std;
using namespace std::placeholders;
Dropdown::Dropdown() {
	currentResolution = nullptr;
	dropdownContent = nullptr;
	currentWidth = 800;
	currentHeight = 600;
}

Dropdown::~Dropdown() {
	
}

bool Dropdown::Init() {
	this->LoadImage("assets/img/dropdown.png");
	this->SetSize(227, 32);
	this->SetLeftClickEvent(bind(&Dropdown::ToggleDropdown, this));
	this->Show();

	currentResolution = new TextLine();
	currentResolution->SetParent(this);
	currentResolution->SetFont("assets/font/Bangers-Regular.ttf", 25);
	currentResolution->SetColor(255, 255, 255);
	currentResolution->SetText("800 x 600");
	currentResolution->SetLeftClickEvent(bind(&Dropdown::ToggleDropdown, this));
	currentResolution->SetPosition(20, 2);
	currentResolution->Show();

	dropdownContent = new Image;
	dropdownContent->LoadImage("assets/img/object-blue.png");
	dropdownContent->SetSize(227, 200);

	/*
	* Construiesc rezolutiile curente
	*/

	int resolutions[6][2] = {
		{800, 600},
		{1280, 720},
		{1440, 900},
		{1680, 1050},
		{1920, 1080},
		{2560, 1440}
	};

	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	int screenWidth = DM.w;
	int screenHeight = DM.h;
	cout << "Monitorul tau are o rata de refresh de " << DM.refresh_rate << " Hz.\n";


	ResolutionItem* tmpItem;
	int count = 0;

	for (int i = 0; i < 6; ++i) {
		if (screenWidth >= resolutions[i][0] && screenHeight >= resolutions[i][1]) {
			count++;
			tmpItem = new ResolutionItem;
			tmpItem->Init(resolutions[i][0], resolutions[i][1]);
			tmpItem->SetParent(dropdownContent);
			tmpItem->SetPosition(0, 30 * i);
			tmpItem->SetEvent(bind(&Dropdown::SetResolution, this, _1, _2));
			tmpItem->Show();
		}
	}

	dropdownContent->SetSize(227, count * 30);
	return true;
}

void Dropdown::SetResolution(int width, int height) {
	char tmpBuffer[32];
	snprintf(tmpBuffer, 32, "%d x %d", width, height);

	currentWidth = width;
	currentHeight = height;

	currentResolution->SetText(tmpBuffer);
	dropdownContent->Hide();
}

void Dropdown::ToggleDropdown() {
	if (dropdownContent->isShow()) {
		dropdownContent->Hide();
	}
	else {
		dropdownContent->Show();
		dropdownContent->SetPosition(this->GetPosition().x, this->GetPosition().y + 32);
	}
}

XYPair Dropdown::GetResolution() {
	XYPair tmp = { currentWidth , currentHeight };

	return tmp;
	
}