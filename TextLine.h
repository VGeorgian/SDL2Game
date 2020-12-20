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
	void SetColor(uint8_t r, uint8_t g, uint8_t b);
	void SetColor(SDL_Color color);
	//void SetText(char* text);
	void SetText(const char sourceText[]);
	void SetFont(const char path[], const unsigned int size);
	void GenerateTexture();
	void Render();
};