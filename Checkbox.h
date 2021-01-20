#pragma once
#include "Image.h"

class Checkbox : public Image {
	Image* arrow;
	bool checked;
public:
	Checkbox();
	~Checkbox();
	bool Init();
	void SwitchStatus();
	void SetStatus(bool status);
	bool GetStatus();
};