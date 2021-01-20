#pragma once
#include "Image.h"
#include "TextLine.h"

class ResolutionItem : public Image {
	TextLine* text;
	int width, height;

	std::function<void(int, int)> callback_func;
public:
	ResolutionItem();
	~ResolutionItem();

	bool Init(int width, int height);

	void OnMouseIn();
	void OnMouseOut();

	void OnLeftClick();
	void SetEvent(function<void(int, int)> callback_func);
};