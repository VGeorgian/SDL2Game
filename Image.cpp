#include "Image.h"

Image::Image() {
    texture = nullptr;
}

Image::~Image() {
    SDL_DestroyTexture(texture);
}

bool Image::LoadImage(const char path[]) {
    SDL_Surface* image = nullptr;
    SDL_RWops* rwop = nullptr;

    rwop = SDL_RWFromFile(path, "rb");

    if (!rwop) {
        printf("SDL_RWFromFile: %s\n", SDL_GetError());
        return false;
    }

    image = IMG_Load_RW(rwop, 1);

    if (!image) {
        printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
        // handle error
        return false;
    }

    texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    //SDL_RWclose(rwop);
    return true;
}

void Image::Render() {
    if (texture) {
        SDL_RenderCopy(renderer, texture, NULL, &dstMask);
    }

}