#include "image.hpp"
#include "utility/macro.hpp"
#include <SDL/SDL_image.h>
#include <stdio.h>

Image loadImage(const char *path)
{
    FILE *fp = fopen(path, "r");
    if (fp == NULL)
    {
        ERROR("image file not found: [%s]", path);
    }
    IMG_Init(IMG_INIT_PNG);
    SDL_Surface *surface = IMG_Load(path);
    return {(unsigned char *)surface->pixels, glm::ivec2(surface->w, surface->h)};
}
