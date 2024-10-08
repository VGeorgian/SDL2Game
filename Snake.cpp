#include "Snake.h"
#include "TextLine.h"

Snake::Snake() {
	direction = 2;
	timerMoving.SetDelay(0);
	field = nullptr;
	fruit = nullptr;
	gameOverText = nullptr;
	gameOverScreen = nullptr;
	startScreen = nullptr;
	closeButton = nullptr;
	restartButton = nullptr;
	startButton = nullptr;
	scoreText = nullptr;
	positionX = 13;
	positionY = 8;
	sprint = false;
	isStarted = false;

	memset(fruitField, false, sizeof(bool) * FIELD_WIDTH * FIELD_HEIGHT);
}

Snake::~Snake() {
	if (nullptr != field)
		delete field;

	if (nullptr != fruit)
		delete fruit;

	if (nullptr != gameOverText)
		delete gameOverText;

	if (nullptr != gameOverScreen)
		delete gameOverScreen;

	if (nullptr != startScreen)
		delete startScreen;

	if (nullptr != closeButton)
		delete closeButton;

	if (nullptr != restartButton)
		delete restartButton;

	if (nullptr != startButton)
		delete startButton;

	if (nullptr != scoreText)
		delete scoreText;
}

bool Snake::Init() {
	CHECK(this->LoadImage("assets/img/snake-board.png"), "this->LoadImage()", __LINE__, __FILE__);
	//this->LoadImage("assets/img/snake-board.png");
	this->SetSize(800, 600);
	this->SetVerticalCenterPosition();
	this->SetHorizontalCenterPosition();
	this->SetFocus();
	this->AddMovableTag();
	this->Show();

	field = new Image;
	CHECK(field->LoadImage("assets/img/snake-field.png"), "field->LoadImage()", __LINE__, __FILE__);
	//field->LoadImage("assets/img/snake-field.png");
	field->SetParent(this);
	field->SetPosition(24, 130);
	field->SetHorizontalCenterPosition();
	field->SetSize(750, 450);
	field->Show();

	startScreen = new Image;
	CHECK(startScreen->LoadImage("assets/img/snake-game-over.png"), "startScreen->LoadImage()", __LINE__, __FILE__);
	//startScreen->LoadImage("assets/img/snake-game-over.png");
	startScreen->SetParent(field);
	startScreen->SetPosition(0, 0);
	startScreen->SetSize(750, 450);
	startScreen->Show();

	startButton = new MenuButton();
	CHECK(startButton->Init("START", 150), "startButton->Init()", __LINE__, __FILE__);
	//startButton->Init("START", 150);
	startButton->SetParent(startScreen);
	startButton->SetPosition(230, 150);
	startButton->SetHorizontalCenterPosition();
	startButton->SetLeftClickEvent(bind(&Snake::StartGame, this));
	startButton->Show();

	gameOverScreen = new Image;
	CHECK(gameOverScreen->LoadImage("assets/img/snake-game-over.png"), "gameOverScreen->LoadImage()", __LINE__, __FILE__);
	//gameOverScreen->LoadImage("assets/img/snake-game-over.png");
	gameOverScreen->SetParent(field);
	gameOverScreen->SetPosition(0, 0);
	gameOverScreen->SetSize(750, 450);

	gameOverText = new TextLine;
	gameOverText->SetParent(gameOverScreen);
	CHECK(gameOverText->SetFont("assets/font/Bangers-Regular.ttf", 100), "gameOverText->SetFont()", __LINE__, __FILE__);
	CHECK(gameOverText->SetColor(255, 255, 255), "gameOverText->SetColor()", __LINE__, __FILE__);
	CHECK(gameOverText->SetText("GAME OVER"), "gameOverText->SetText()", __LINE__, __FILE__);
	//gameOverText->SetFont("assets/font/Bangers-Regular.ttf", 100);
	//gameOverText->SetColor(255, 255, 255);
	//gameOverText->SetText("GAME OVER");
	gameOverText->SetPosition(185, 50);
	gameOverText->Show();

	scoreText = new TextLine;
	scoreText->SetParent(this);
	CHECK(scoreText->SetFont("assets/font/Bangers-Regular.ttf", 30), "scoreText->SetFont()", __LINE__, __FILE__);
	CHECK(scoreText->SetColor(255, 255, 255), "scoreText->SetColor()", __LINE__, __FILE__);
	CHECK(scoreText->SetText("SCOR: 0"), "scoreText->SetText()", __LINE__, __FILE__);
	//scoreText->SetFont("assets/font/Bangers-Regular.ttf", 30);
	//scoreText->SetColor(255, 255, 255);
	//scoreText->SetText("SCOR: 0");
	scoreText->SetPosition(30, 90);
	scoreText->Show();

	restartButton = new MenuButton();
	CHECK(restartButton->Init("Restart"), "restartButton->Init()", __LINE__, __FILE__);
	//restartButton->Init("Restart");
	restartButton->SetParent(gameOverScreen);
	restartButton->SetPosition(320, 260);
	restartButton->SetHorizontalCenterPosition();
	restartButton->SetLeftClickEvent(bind(&Snake::StartGame, this));
	restartButton->Show();

	Image* tmpImg = new Image;
	CHECK(tmpImg->LoadImage("assets/img/snake.png"), "tmpImg->LoadImage()", __LINE__, __FILE__);
	//tmpImg->LoadImage("assets/img/snake.png");
	tmpImg->SetParent(field);
	tmpImg->SetPosition((positionX - 1) * 30, (positionY - 1) * 30);
	tmpImg->SetSize(30, 30);
	tmpImg->Show();

	snake.push_back(tmpImg);

	fruit = new Image;
	CHECK(fruit->LoadImage("assets/img/snake-fruit.png"), "fruit->LoadImage()", __LINE__, __FILE__);
	//fruit->LoadImage("assets/img/snake-fruit.png");
	fruit->SetParent(field);
	fruit->SetPosition(10 * 30, 10 * 30);
	fruit->SetSize(30, 30);
	fruit->Show();

	closeButton = new Image;
	CHECK(closeButton->LoadImage("assets/img/close_button.png"), "closeButton->LoadImage()", __LINE__, __FILE__);
	//closeButton->LoadImage("assets/img/close_button.png");
	closeButton->SetParent(this);
	closeButton->SetPosition(750, 15);
	closeButton->SetSize(30, 30);
	closeButton->SetLeftClickEvent(bind(&Snake::CloseGame, this));
	closeButton->Show();


	isStarted = false;
	startScreen->BringToFront();

	return true;
}

void Snake::StartGame() {
	while (snake.size() > 1) {
		snake.begin()[1]->Hide();
		snake.begin()[1]->EnableSelfDestroy();
		snake.erase(snake.begin() + 1);
	}

	gameOverScreen->Hide();
	startScreen->Hide();
	isStarted = true;
	direction = 2;
	GenerateFruit();
	positionX = 13;
	positionY = 8;
	//TODO: Add autodestroy variable

	
	Image* tmpImg;
	for (int i = 0; i < 100; ++i){
		tmpImg = new Image;
		tmpImg->LoadImage("assets/img/snake.png");
		tmpImg->SetParent(field);
		tmpImg->SetPosition(0, 0);
		tmpImg->SetSize(30, 30);
		tmpImg->Show();

		snake.push_back(tmpImg);
	}
	
}

void Snake::OpenGame() {
	BringToFront();
	Show();
	startScreen->Show();
	gameOverScreen->Hide();
	isStarted = false;
}

void Snake::CloseGame() {
	Hide();
	isStarted = false;
}

void Snake::GenerateFruit(){
	//Genereaza o noua pozitie a fructului, intr-un slot unde nu se gaseste sarpele
	int i, tmp, tmpArray[FIELD_WIDTH * FIELD_HEIGHT];
	//cout << "Elementul: " << (positionY - 1) * 25 + positionX << endl;
	memset(fruitField, 0, sizeof(bool) * FIELD_WIDTH * FIELD_HEIGHT);
	memset(tmpArray, 0, sizeof(bool) * FIELD_WIDTH * FIELD_HEIGHT);

	auto snakeHead = snake.begin();

	for (i = 0; i < snake.size(); ++i) {
		tmp = snakeHead[i]->GetRelativePosition().y / 30 * 25 + snakeHead[i]->GetRelativePosition().x / 30;
		fruitField[tmp] = true;
	}

	tmp = 0;

	for (i = 0; i < FIELD_WIDTH * FIELD_HEIGHT; i++) {
		if (!fruitField[i])
			tmpArray[tmp++] = i;
	}

	i = rand() % tmp;
	//cout << "Linia: " << tmpArray[i] / FIELD_WIDTH << "  coloana: " << tmpArray[i] % FIELD_WIDTH << endl;

	fruit->SetPosition(tmpArray[i] % FIELD_WIDTH * 30, tmpArray[i] / FIELD_WIDTH * 30);
	fruit->BringToFront();
}

void Snake::OnKeyPress(bool KEYS[], int currentKey) {
	if (KEYS[SDL_SCANCODE_A] || KEYS[SDL_SCANCODE_LEFT]) {
		direction = 0;
		//cout << "Left";
	}
	if (KEYS[SDL_SCANCODE_W] || KEYS[SDL_SCANCODE_UP]) {
		direction = 1;
		//cout << "Left";
	}
	if (KEYS[SDL_SCANCODE_D] || KEYS[SDL_SCANCODE_RIGHT]) {
		direction = 2;
		//cout << "Left";
	}
	if (KEYS[SDL_SCANCODE_S] || KEYS[SDL_SCANCODE_DOWN]) {
		direction = 3;
		//cout << "Left";
	}
	if (currentKey == SDL_SCANCODE_LSHIFT) {
		sprint = true;
	}
}
void Snake::OnKeyRelease(bool KEYS[], int currentKey) {
	if (currentKey == SDL_SCANCODE_LSHIFT) {
		sprint = false;
	}
}

void Snake::Update() {
	if(isStarted)
		if (timerMoving.TimeElasped()) {
			char nextX = positionX, nextY = positionY;
			struct XYPair tmpPosition;
			bool eatFruit = false;
			auto snakeHead = snake.begin();

			switch (direction) {
			case 0:
				if (positionX == 1)
					positionX = FIELD_WIDTH + 1;
				--positionX;
				break;
			case 1:
				if (positionY == 1)
					positionY = FIELD_HEIGHT + 1;
				--positionY;
				break;
			case 2:
				if (positionX == FIELD_WIDTH)
					positionX = 0;
				++positionX;
				break;
			case 3:
				if (positionY == FIELD_HEIGHT)
					positionY = 0;
				++positionY;
				break;
			default:
				break;
			}


			// Verific daca urmatoarea pozitie este tot parte din sarpe
			for (int i = 1; i < snake.size(); ++i) {
				if (snakeHead[i]->GetRelativePosition().x == 30 * (positionX - 1) && snakeHead[i]->GetRelativePosition().y == 30 * (positionY - 1)) {
					snakeHead[i]->LoadImage("assets/img/object-red.png");
					isStarted = false;
					gameOverScreen->Show();
					gameOverScreen->BringToFront();
					return;
				}
			}

			tmpPosition = fruit->GetRelativePosition();
			if (tmpPosition.x == 30 * (positionX - 1) && tmpPosition.y == 30 * (positionY - 1)) {
				eatFruit = true;
			}


			tmpPosition = snakeHead[0]->GetRelativePosition();
			snakeHead[0]->SetPosition(30 * (positionX - 1), 30 * (positionY - 1));

			for (int i = 1; i < snake.size(); ++i) {
				struct XYPair tmpPosition2;
				tmpPosition2 = snakeHead[i]->GetRelativePosition();
				snakeHead[i]->SetPosition(tmpPosition.x, tmpPosition.y);
				tmpPosition = tmpPosition2;
			}

			if (eatFruit) {
				Image* tmpSnake = new Image;
				tmpSnake->LoadImage("assets/img/snake.png");
				tmpSnake->SetParent(field);
				tmpSnake->SetPosition(tmpPosition.x, tmpPosition.y);
				tmpSnake->SetSize(30, 30);
				tmpSnake->Show();

				snake.push_back(tmpSnake);

				GenerateFruit();

				char tmpBuffer[64];
				snprintf(tmpBuffer, 64, "SCOR: %zd", snake.size());
				scoreText->SetText(tmpBuffer);
			}

			if(sprint)
				timerMoving.SetDelay(200);
			else
				timerMoving.SetDelay(500);
		}
}

