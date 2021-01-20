#include <iostream>
#include <fstream>
#include <SDL_mixer.h>
#include "Settings.h"

using namespace std;

Settings::Settings() {
	title = nullptr;
	saveButton = nullptr;
	screenSizeLabel = nullptr;
	musicStatusLabel = nullptr;
	volumeLabel = nullptr;
	volumeRange = nullptr;
	musicCheckbox = nullptr;
	resolutionDropdown = nullptr;

	currentResolution = { 800, 600 };
	musicPlaying = false;
	musicVolume = 0;
}

Settings::~Settings() {
	if (nullptr != title)
		delete title;

	if (nullptr != saveButton)
		delete saveButton;

	if (nullptr != screenSizeLabel)
		delete screenSizeLabel;

	if (nullptr != musicStatusLabel)
		delete musicStatusLabel;

	if (nullptr != volumeLabel)
		delete volumeLabel;

	if (nullptr != volumeRange)
		delete volumeRange;

	if (nullptr != musicCheckbox)
		delete musicCheckbox;

	if (nullptr != resolutionDropdown)
		delete resolutionDropdown;
}

void Settings::ReadSettingsFromFile() {
	ifstream IN("game.config", ifstream::in);
	IN >> currentResolution.x >> currentResolution.y >> musicPlaying >> musicVolume;
}

void Settings::SaveSettings() {
	currentResolution = resolutionDropdown->GetResolution();
	musicPlaying = musicCheckbox->GetStatus();
	musicVolume = volumeRange->GetValue();

	if (!musicPlaying) {
		Mix_PauseMusic();
	}
	else {
		Mix_ResumeMusic();
	}

	ofstream OUT("game.config", ifstream::out);
	OUT << currentResolution.x << "\n";
	OUT << currentResolution.y << "\n";
	OUT << musicPlaying << "\n";
	OUT << musicVolume << "\n";



	Mix_VolumeMusic(musicVolume);
	
}

bool Settings :: Init() {
	this->LoadImage("assets/img/background_menu.jpg");
	this->SetSize(GetWindowSize().x, GetWindowSize().y);
	this->Show();

	/*
	**  Citesc setarile din fisier
	*/
	
	ReadSettingsFromFile();

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	Mix_Music* bgMusic = NULL;
	bgMusic = Mix_LoadMUS("assets/sound/background.mp3");
	Mix_PlayMusic(bgMusic, 0);
	Mix_VolumeMusic(musicVolume);

	if (!musicPlaying) {
		Mix_PauseMusic();
	}
	else {
		Mix_ResumeMusic();
	}

	title = new TextLine();
	title->SetParent(this);
	title->SetFont("assets/font/Bangers-Regular.ttf", 50);
	title->SetColor(255, 255, 255);
	title->SetText("SETARI");
	title->SetPosition(30, 60);
	title->Show();

	saveButton = new MenuButton();
	saveButton->Init("SALVEAZÃ SETARI", 60);
	saveButton->SetPosition(30, GetWindowSize().y - 100);
	saveButton->SetParent(this);
	saveButton->SetLeftClickEvent(bind(&Settings::SaveSettings, this));
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

	volumeRange = new RangeInput;
	volumeRange->Init(300);
	volumeRange->SetParent(this);
	volumeRange->SetPosition(140, 280);
	volumeRange->SetValue(musicVolume);

	musicCheckbox = new Checkbox;
	musicCheckbox->Init();
	musicCheckbox->SetParent(this);
	musicCheckbox->SetPosition(230, 230);
	musicCheckbox->Show();
	musicCheckbox->SetStatus(musicPlaying);

	resolutionDropdown = new Dropdown;
	resolutionDropdown->Init();
	resolutionDropdown->SetParent(this);
	resolutionDropdown->SetPosition(220, 180);
	resolutionDropdown->Show();

	return true;
}

void Settings::ShowSettings() {
	ReadSettingsFromFile();

	resolutionDropdown->SetResolution(currentResolution.x, currentResolution.y);
	musicCheckbox->SetStatus(musicPlaying);
	volumeRange->SetValue(musicVolume);
	this->Show();
}
