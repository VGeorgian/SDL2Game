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
    
    CHECK_ERROR(rwop, "Eroare SDL_RWFromFile", SDL_GetError(), __LINE__, __FILE__);

    image = IMG_Load_RW(rwop, 1);

    CHECK_ERROR(image, "Eroare IMG_Load_RW", IMG_GetError(), __LINE__, __FILE__);

    texture = SDL_CreateTextureFromSurface(renderer, image);

    if (!texture) {
        SDL_FreeSurface(image);
    }
    CHECK_ERROR(texture, "Eroare SDL_CreateTextureFromSurface", SDL_GetError(), __LINE__, __FILE__);

    SDL_FreeSurface(image);
    //SDL_RWclose(rwop);
    return true;
}

void Image::Render() {
    if (texture) {
        if(srcMask.w != 0 && srcMask.h != 0)
            SDL_RenderCopy(renderer, texture, &srcMask, &dstMask);
        else
            SDL_RenderCopy(renderer, texture, NULL, &dstMask);
    }
}