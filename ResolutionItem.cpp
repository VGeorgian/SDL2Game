#include "ResolutionItem.h"

ResolutionItem::ResolutionItem() {
	text = nullptr;
	width = 0;
	height = 0;
}

ResolutionItem::~ResolutionItem() {
	if (text != nullptr)
		delete text;
}


bool ResolutionItem::Init(int width, int height) {

	CHECK(this->LoadImage("assets/img/dropdown-item.png"), "this->LoadImage()", __LINE__, __FILE__);
	//this->LoadImage("assets/img/dropdown-item.png");
	this->SetSize(227, 32);
	this->Show();

	this->srcMask.w = 64;
	this->srcMask.h = 32;

	this->width = width;
	this->height = height;

	char tmpBuffer[32];
	snprintf(tmpBuffer, 32, "%d x %d", width, height);

	text = new TextLine;
	text->SetParent(this);
	CHECK(text->SetFont("assets/font/Bangers-Regular.ttf", 25), "text->SetFont()", __LINE__, __FILE__);
	CHECK(text->SetColor(255, 255, 255), "text->SetColor()", __LINE__, __FILE__);
	CHECK(text->SetText(tmpBuffer), "text->SetText()", __LINE__, __FILE__);
	//text->SetFont("assets/font/Bangers-Regular.ttf", 25);
	//text->SetColor(255, 255, 255);
	//text->SetText(tmpBuffer);
	text->SetLeftClickEvent(bind(&ResolutionItem::OnLeftClick, this));
	text->SetPosition(10, 2);
	text->Show();



	return true;
}

void ResolutionItem::SetEvent(function<void(int, int)> callback_func) {
	this->callback_func = callback_func;
}

void ResolutionItem::OnLeftClick() {
	if (callback_func) {
		callback_func(width, height);
	}
}

void ResolutionItem::OnMouseIn() {
	this->srcMask.y = 32;
}


void ResolutionItem::OnMouseOut() {
	this->srcMask.y = 0;
}