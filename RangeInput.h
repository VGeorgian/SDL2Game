#pragma once
#include "Image.h"
#include "TextLine.h"

class RangeInput : public Image {
	Image* cursor;
	TextLine* valueLabel;
	bool followCursor;
	int value;
public:
	RangeInput();
	~RangeInput();
	void Update();
	void OnLeftClick();
	bool Init(const unsigned int& length = 100);
	void OnMouseRelease();
	void SetLength(const unsigned int &length);
	int GetValue();
	void SetValue(const unsigned int &value);
};