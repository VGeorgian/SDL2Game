#include "Snake.h"


Snake::Snake() {
	direction = 2;
	timerMoving.SetDelay(0);
	field = nullptr;
	fruit = nullptr;
	positionX = 13;
	positionY = 8;
	sprint = false;
}

bool Snake::Init() {
	this->LoadImage("assets/img/snake-board.png");
	this->SetSize(800, 600);
	this->SetVerticalCenterPosition();
	this->SetHorizontalCenterPosition();
	this->SetFocus();
	this->AddMovableTag();
	this->Show();

	field = new Image;
	field->LoadImage("assets/img/snake-field.png");
	field->SetParent(this);
	field->SetPosition(24, 130);
	field->SetHorizontalCenterPosition();
	field->SetSize(750, 450);
	field->Show();

	Image* tmpImg = new Image;
	tmpImg->LoadImage("assets/img/snake.png");
	tmpImg->SetParent(field);
	tmpImg->SetPosition(10 * 30, 10 * 30);
	tmpImg->SetSize(30, 30);
	tmpImg->Show();

	fruit = new Image;
	fruit->LoadImage("assets/img/snake-fruit.png");
	fruit->SetParent(field);
	fruit->SetPosition(10 * 30, 10 * 30);
	fruit->SetSize(30, 30);
	fruit->Show();



	snake.push_back(tmpImg);
	/*for (int i = 0; i < 14; ++i) {
		Image* tmpSnake = new Image;
		tmpSnake->LoadImage("assets/img/snake.png");
		tmpSnake->SetParent(field);
		tmpSnake->SetPosition(i * 30, i * 30);
		tmpSnake->SetSize(30, 30);
		tmpSnake->Show();

		snake.push_back(tmpSnake);
	}*/


	return true;
}

void Snake::OnKeyPress(bool KEYS[], unsigned int currentKey) {
	if (KEYS[SDL_SCANCODE_A]) {
		direction = 0;
		//cout << "Left";
	}
	if (KEYS[SDL_SCANCODE_W]) {
		direction = 1;
		//cout << "Left";
	}
	if (KEYS[SDL_SCANCODE_D]) {
		direction = 2;
		//cout << "Left";
	}
	if (KEYS[SDL_SCANCODE_S]) {
		direction = 3;
		//cout << "Left";
	}
	if (currentKey == SDL_SCANCODE_LSHIFT) {
		sprint = true;
	}
}
void Snake::OnKeyRelease(bool KEYS[], unsigned int currentKey) {
	if (currentKey == SDLK_LSHIFT) {
		sprint = false;
	}
}

void Snake::Update() {
	if (timerMoving.TimeElasped()) {
		char nextX = positionX, nextY = positionY;
		struct XYPair tmpPosition;
		bool eatFruit = false;

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

		auto snakeHead = snake.begin();

		// Verific daca urmatoarea pozitie este tot parte din sarpe
		for (int i = 1; i < snake.size(); ++i) {
			if (snakeHead[i]->GetRelativePosition().x == 30 * (positionX - 1) && snakeHead[i]->GetRelativePosition().y == 30 * (positionY - 1)) {
				cout << "Sfarsitul jocului!\n";
				break;
			}
		}

		tmpPosition = fruit->GetRelativePosition();
		if (tmpPosition.x == 30 * (positionX - 1) && tmpPosition.y == 30 * (positionY - 1)) {
			eatFruit = true;
			cout << "Manca fruct\n";
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
			cout << "Adaug la " << tmpPosition.x << " " << tmpPosition.y << endl;
			Image* tmpSnake = new Image;
			tmpSnake->LoadImage("assets/img/snake.png");
			tmpSnake->SetParent(field);
			tmpSnake->SetPosition(tmpPosition.x, tmpPosition.y);
			tmpSnake->SetSize(30, 30);
			tmpSnake->Show();

			snake.push_back(tmpSnake);

		}


		if(sprint)
			timerMoving.SetDelay(200);
		else
			timerMoving.SetDelay(500);
	}
}

