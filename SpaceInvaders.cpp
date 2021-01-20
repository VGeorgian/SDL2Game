#include <iostream>
#include "SpaceInvaders.h"
using namespace std;

SpaceInvaders::SpaceInvaders() {
	closeButton = nullptr;
	gameField = nullptr;
	startScreen = nullptr;
	startButton = nullptr;
	gameOverScreen = nullptr;
	player = nullptr;
	scoreText = nullptr;
	levelText = nullptr;
	restartButton = nullptr;

	playerPosition = 10;
	currentLevel = 0;
	isStarted = false;
	direction = 0;
	score = 0;
	shootTimer.SetDelay(0);
}

SpaceInvaders::~SpaceInvaders() {
	if (nullptr != closeButton) {
		delete closeButton;
	}

	if (nullptr != gameField) {
		delete gameField;
	}

	if (nullptr != startScreen) {
		delete startScreen;
	}

	if (nullptr != startButton) {
		delete startButton;
	}

	if (nullptr != gameOverScreen) {
		delete gameOverScreen;
	}

	if (nullptr != player) {
		delete player;
	}

	if (nullptr != scoreText) {
		delete scoreText;
	}

	if (nullptr != levelText) {
		delete levelText;
	}

	if (nullptr != restartButton) {
		delete restartButton;
	}
}

void SpaceInvaders::StartGame() {
	while(enemies.size()) {
		enemies.begin()[0]->EnableSelfDestroy();
		enemies.begin()[0]->Hide();
		enemies.erase(enemies.begin());
	}

	while (playerAmmo.size()) {
		playerAmmo.begin()[0]->EnableSelfDestroy();
		playerAmmo.begin()[0]->Hide();
		playerAmmo.erase(playerAmmo.begin());
	}

	score = 0;
	currentLevel = 0;
	scoreText->SetText("SCOR: 0");
	levelText->SetText("NIVEL: 2");
	isStarted = true;
	startScreen->Hide();
	gameOverScreen->Hide();
}


void SpaceInvaders::EndGame() {
	isStarted = false;
	gameOverScreen->Show();
}

bool SpaceInvaders::Init() {
	this->LoadImage("assets/img/spaceinvaders-board.png");
	this->SetSize(800, 600);
	this->SetVerticalCenterPosition();
	this->SetHorizontalCenterPosition();
	this->SetFocus();
	this->AddMovableTag();

	closeButton = new Image;
	closeButton->LoadImage("assets/img/close_button.png");
	closeButton->SetParent(this);
	closeButton->SetPosition(750, 15);
	closeButton->SetSize(30, 30);
	closeButton->SetLeftClickEvent(bind(&SpaceInvaders::CloseGame, this));
	closeButton->Show();

	gameField = new Image;
	gameField->LoadImage("assets/img/object-black.png");
	gameField->SetParent(this);
	gameField->SetPosition(24, 120);
	gameField->SetHorizontalCenterPosition();
	gameField->SetSize(750, 450);
	gameField->Show();

	player = new Image;
	player->LoadImage("assets/img/space-player.png");
	player->SetParent(gameField);
	player->SetPosition(10, 400);
	player->SetSize(48, 24);
	player->Show();

	startScreen = new Image;
	startScreen->LoadImage("assets/img/snake-game-over.png");
	startScreen->SetParent(gameField);
	startScreen->SetPosition(0, 0);
	startScreen->SetSize(750, 450);
	startScreen->Show();

	gameOverScreen = new Image;
	gameOverScreen->LoadImage("assets/img/snake-game-over.png");
	gameOverScreen->SetParent(gameField);
	gameOverScreen->SetPosition(0, 0);
	gameOverScreen->SetSize(750, 450);

	startButton = new MenuButton();
	startButton->Init("START", 150);
	startButton->SetParent(startScreen);
	startButton->SetPosition(230, 150);
	startButton->SetHorizontalCenterPosition();
	startButton->SetLeftClickEvent(bind(&SpaceInvaders::StartGame, this));
	startButton->Show();

	restartButton = new MenuButton();
	restartButton->Init("Restart");
	restartButton->SetParent(gameOverScreen);
	restartButton->SetPosition(320, 260);
	restartButton->SetHorizontalCenterPosition();
	restartButton->SetLeftClickEvent(bind(&SpaceInvaders::StartGame, this));
	restartButton->Show();

	scoreText = new TextLine;
	scoreText->SetParent(this);
	scoreText->SetFont("assets/font/NerkoOne-Regular.ttf", 20);
	scoreText->SetColor(255, 255, 255);
	scoreText->SetText("NIVEL: 1");
	scoreText->SetPosition(30, 94);
	scoreText->Show();

	levelText = new TextLine;
	levelText->SetParent(this);
	levelText->SetFont("assets/font/NerkoOne-Regular.ttf", 20);
	levelText->SetColor(255, 255, 255);
	levelText->SetText("SCOR: 0");
	levelText->SetPosition(150, 94);
	levelText->Show();
	

	return true;
}

void SpaceInvaders::GenerateEnemies() {
	SpaceInvadersEnemy* tmpEnemy;
	for (int i = 0; i < 20; ++i) {
		tmpEnemy = new SpaceInvadersEnemy;
		if(currentLevel == 1)
			tmpEnemy->LoadImage("assets/img/space-enemy.png");
		else if (currentLevel == 2) {
			tmpEnemy->LoadImage("assets/img/space-enemy2.png");
		}
		else {
			tmpEnemy->LoadImage("assets/img/space-enemy3.png");
		}

		tmpEnemy->SetParent(gameField);
		tmpEnemy->SetPosition(30 + 70 * (i % 10), 20 + 70 * (i / 10));
		tmpEnemy->SetSize(40, 30);
		tmpEnemy->SetLifePoints(currentLevel);
		tmpEnemy->Show();

		enemies.push_back(tmpEnemy);
	}
}

void SpaceInvaders::OnKeyPress(bool KEYS[], int currentKey) {
	if (isStarted) {
		if (KEYS[SDL_SCANCODE_A]) {
			direction = 1;
		}
		if (KEYS[SDL_SCANCODE_D]) {
			direction = 2;
		}
		if (KEYS[SDL_SCANCODE_SPACE] && shootTimer.TimeElasped()) {
			shootTimer.SetDelay(300);
			Image* tmpAmmo = new Image;
			tmpAmmo->LoadImage("assets/img/object-red.png");
			tmpAmmo->SetParent(gameField);
			tmpAmmo->SetPosition(player->GetRelativePosition().x + 20, 395);
			tmpAmmo->SetSize(5, 20);
			tmpAmmo->Show();

			playerAmmo.push_back(tmpAmmo);
		}
	}
}

void SpaceInvaders::OnKeyRelease(bool KEYS[], int currentKey) {
	if (currentKey == SDL_SCANCODE_A && direction == 1) {
		direction = 0;
	}
	if (currentKey == SDL_SCANCODE_D && direction == 2) {
		direction = 0;
	}
}


void SpaceInvaders::Update() {
	if (isStarted) {
		SDL_Rect* tmpRect = nullptr;
		if (direction == 1 && playerPosition > 10) {
			--playerPosition;
		}
		else if (direction == 2 && playerPosition < 688) {
			++playerPosition;
		}
		player->SetPosition(playerPosition, 400);

		if (!enemies.size()) {
			if (currentLevel == 3) {
				EndGame();
			}
			else {
				++currentLevel;
				GenerateEnemies();

				char tmpBuffer[32];
				snprintf(tmpBuffer, 32, "NIVEL: %d", currentLevel);
				levelText->SetText(tmpBuffer);
			}
		}
		for (int i = 0; i < playerAmmo.size(); ++i) {
			// Dealocare memorie munitie dupa iesire din ecran
			if (playerAmmo.begin()[i]->GetRelativePosition().y < 10) {
				playerAmmo.begin()[i]->EnableSelfDestroy();
				playerAmmo.begin()[i]->Hide();
				playerAmmo.erase(playerAmmo.begin() + i);
				--i;
			}

			else {
				tmpRect = playerAmmo.begin()[i]->GetDstRectPointer();
				playerAmmo.begin()[i]->SetPosition(playerAmmo.begin()[i]->GetRelativePosition().x, playerAmmo.begin()[i]->GetRelativePosition().y - 1);
				for (int j = 0; j < enemies.size(); ++j) {
					if (enemies.begin()[j]->CheckFocus(tmpRect->x, tmpRect->y) || enemies.begin()[j]->CheckFocus(tmpRect->x + tmpRect->w, tmpRect->y)) {
						if (!enemies.begin()[j]->DecreaseLifePoints()) {
							enemies.begin()[j]->EnableSelfDestroy();
							enemies.begin()[j]->Hide();
							enemies.erase(enemies.begin() + j);
							++score;

							char tmpBuffer[32];
							snprintf(tmpBuffer, 32, "SCOR: %d", score);
							scoreText->SetText(tmpBuffer);
						}

						playerAmmo.begin()[i]->EnableSelfDestroy();
						playerAmmo.begin()[i]->Hide();
						playerAmmo.erase(playerAmmo.begin() + i);

						return;
					}
				}
			}
		}
	}


}

void SpaceInvaders::OpenGame() {
	startScreen->BringToFront();
	startScreen->Show();
	this->Show();
}

void SpaceInvaders::CloseGame() {
	gameOverScreen->Hide();
	this->Hide();
}