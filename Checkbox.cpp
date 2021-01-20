#include "Checkbox.h"

Checkbox::Checkbox() {
	checked = false;
	arrow = nullptr;
}

Checkbox::~Checkbox() {
	if (nullptr != arrow)
		delete arrow;
}

bool Checkbox::Init() {
	this->LoadImage("assets/img/checkbox.png");
	this->SetSize(32, 32);
	this->SetLeftClickEvent(bind(&Checkbox::SwitchStatus, this));
	this->Show();

	arrow = new Image;
	arrow->LoadImage("assets/img/checkbox-arrow.png");
	arrow->SetParent(this);
	arrow->SetSize(32, 32);
	arrow->SetPosition(0, 0);
	arrow->SetLeftClickEvent(bind(&Checkbox::SwitchStatus, this));

	return true;
}

void Checkbox::SetStatus(bool status) {
	checked = status;
	if (checked) {
		arrow->Show();
	}
	else {
		arrow->Hide();
	}
}


void Checkbox::SwitchStatus() {
	if (checked) {
		arrow->Hide();
		checked = false;
	}
	else {
		arrow->Show();
		checked = true;
	}

}

bool Checkbox::GetStatus() {
	return checked;
}

