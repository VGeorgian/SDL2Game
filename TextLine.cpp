#include <string.h>
#include "TextLine.h"

TextLine::TextLine():Interface() {
	//font = TTF_OpenFont("", 20);
	font = nullptr;
	texture = nullptr;
	text = new char[1];
	text[0] = '-';
	color = { 255, 255, 255 };
}

TextLine::~TextLine() {
	if (nullptr != font) {
		TTF_CloseFont(font);
	}

	if (nullptr != texture) {
		SDL_DestroyTexture(texture);
	}
	
	if (nullptr != text) {
		delete[] text;
	}
}

bool TextLine::SetFont(const char path[], const unsigned int size) {
	font = TTF_OpenFont(path, size);

	CHECK_ERROR(font, "TTF_OpenFont(path, size)", TTF_GetError(), __LINE__, __FILE__);
	
	CHECK(GenerateTexture(), "GenerateTexture()", __LINE__, __FILE__);

	return true;
}

TTF_Font* TextLine::GetFont() {
	return font;
}

bool TextLine::SetColor(uint8_t r, uint8_t g, uint8_t b) {
	color = { r, g, b };

	CHECK(GenerateTexture(), "GenerateTexture()", __LINE__, __FILE__);

	return true;
}

bool TextLine::SetColor(SDL_Color color) {
	this->color = color;

	CHECK(GenerateTexture(), "GenerateTexture()", __LINE__, __FILE__);

	return true;
}

bool TextLine::SetText(const char sourceText[]) {
	if (nullptr != text) {
		delete[] text;
	}

	text = new char[strlen(sourceText) + 1];
	strcpy_s(text, strlen(sourceText) + 1, sourceText);
	CHECK(GenerateTexture(), "GenerateTexture()", __LINE__, __FILE__);

	return true;
}

bool TextLine::GenerateTexture() {
	if (nullptr != font) {
		SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);

		CHECK_ERROR(surface, "TTF_RenderText_Blended(font, text, color)", TTF_GetError(), __LINE__, __FILE__);

		texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (nullptr == texture) {
			SDL_FreeSurface(surface);
		}
		CHECK_ERROR(texture, "SDL_CreateTextureFromSurface(renderer, surface)", SDL_GetError(), __LINE__, __FILE__);

		SDL_FreeSurface(surface);
		surface = nullptr;

		SDL_QueryTexture(texture, NULL, NULL, &dstMask.w, &dstMask.h);

		return true;
	}

	return false;
}

void TextLine::Render(){
	if(nullptr != texture)
		SDL_RenderCopy(renderer, texture, NULL, &dstMask);
}