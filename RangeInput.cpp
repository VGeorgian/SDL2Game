#include "RangeInput.h"

RangeInput::RangeInput() {
	
}

RangeInput::~RangeInput() {

}

bool RangeInput::Init() {
	this->LoadImage("assets/img/background_menu.jpg");
	this->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	this->Show();

	return true;
}