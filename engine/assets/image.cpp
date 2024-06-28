#include "image.hpp"
#include <SDL/SDL_image.h>

Image loadImage(const char *path)
{
    IMG_Init(IMG_INIT_PNG);
    SDL_Surface *surface = IMG_Load(path);
    return {(unsigned char *)surface->pixels, glm::ivec2(surface->w, surface->h)};
}
