#include <iostream>
#include "RangeInput.h"

RangeInput::RangeInput() {
	cursor = nullptr;
	valueLabel = nullptr;
	followCursor = false;
	value = 0;
}

RangeInput::~RangeInput() {
	if (cursor)
		delete cursor;
	if (valueLabel)
		delete valueLabel;
}

bool RangeInput::Init(const unsigned int& length) {
	this->LoadImage("assets/img/slider-bar.png");
	this->SetSize(length, 34);
	this->Show();

	cursor = new Image;
	cursor->LoadImage("assets/img/slider-cursor.png");
	cursor->SetParent(this);
	cursor->SetPosition(0, 5);
	cursor->SetSize(4, 25);
	cursor->SetLeftClickEvent(bind(&RangeInput::OnLeftClick, this));
	cursor->Show();

	valueLabel = new TextLine;
	valueLabel->SetFont("assets/font/NerkoOne-Regular.ttf", 20);
	valueLabel->SetParent(this);
	valueLabel->SetColor(255, 255, 255);
	valueLabel->SetText("0");
	valueLabel->SetPosition(0, -10);
	valueLabel->Show();


	return true;
}

void RangeInput::SetLength(const unsigned int& length) {
	this->SetSize(length, 34);
}


void RangeInput::OnMouseRelease() {
	followCursor = false;
}

void RangeInput::OnLeftClick() {
	followCursor = true;
}

void RangeInput::Update() {
	if (followCursor) {
		if (mouseX < this->GetPosition().x)
			cursor->SetPosition(0, 5);
		else if (mouseX > (this->GetPosition().x + this->GetSize().x)) {
			cursor->SetPosition(this->GetSize().x - 4, 5);
		}
		else {
			cursor->SetPosition(mouseX - this->GetPosition().x, 5);
		}
		value = 100 * cursor->GetRelativePosition().x / (this->GetSize().x - 4);

	}

	char tmpBuffer[8];
	snprintf(tmpBuffer, 8, "%d", value);
	valueLabel->SetText(tmpBuffer);
}

void RangeInput::SetValue(const unsigned int& value) {
	this->value = value;
	cursor->SetPosition(value * GetSize().x / 100, 5);
}

int RangeInput::GetValue() {
	return value;
}