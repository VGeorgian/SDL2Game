#include <string.h>
#include "TextLine.h"

TextLine::TextLine():Interface() {
	font = nullptr;
	texture = nullptr;
	text = new char[1];
	text[0] = '0';
	color = { 255, 255, 255 };
}

TextLine::~TextLine() {
	if(nullptr != font)
		TTF_CloseFont(font);
	if(nullptr != texture)
		SDL_DestroyTexture(texture);
	if (nullptr != text)
		delete[] text;
}

void TextLine::SetFont(const char path[], const unsigned int size) {
	font = TTF_OpenFont(path, size);
	Generate();
}


void TextLine::SetColor(uint8_t r, uint8_t g, uint8_t b) {
	color = { r, g, b };
	Generate();
}

void TextLine::SetColor(SDL_Color color) {
	this->color = color;
	Generate();
}

void TextLine::SetText(const char sourceText[]) {
	if (nullptr != text) {
		delete[] text;
		text = nullptr;
	}

	text = new char[strlen(sourceText) + 1];
	strcpy_s(text, strlen(sourceText) + 1, sourceText);
	Generate();
}

void TextLine::Generate() {
	if (nullptr != font) {
		SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);
		if (nullptr == surface) {
			printf("TTFError: %s\n", TTF_GetError());
		}
		texture = SDL_CreateTextureFromSurface(renderer, surface);

		SDL_FreeSurface(surface);

		SDL_QueryTexture(texture, NULL, NULL, &dstMask.w, &dstMask.h);
	}
}

void TextLine::Render(){
	if(nullptr != texture)
		SDL_RenderCopy(renderer, texture, NULL, &dstMask);
}