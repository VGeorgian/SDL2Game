#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "config.h"
#include "Interface.h"

class Image:public Interface {

protected:
    SDL_Texture* texture;

public:
    Image();
    ~Image();

    bool LoadImage(const char path[]);
    void Render();

};