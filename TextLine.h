#pragma once
#include <cstdint>
#include <SDL_ttf.h>
#include "Interface.h"

class TextLine : public Interface {
	TTF_Font* font;
	SDL_Color color;
	SDL_Texture* texture;
	char* text;
public:
	TextLine();
	~TextLine();
	bool SetColor(uint8_t r, uint8_t g, uint8_t b);
	bool SetColor(SDL_Color color);
	//void SetText(char* text);
	bool SetText(const char sourceText[]);
	bool SetFont(const char path[], const unsigned int size);
	TTF_Font* GetFont();
	bool GenerateTexture();
	void Render();
};