#include "image.hpp"
#include "utility/macro.hpp"
#include "vendor/stb/stb_image.h"
#include <stdio.h>

Image loadImage(const char *path)
{
    ARG_CHECK(fopen(path, "r") == NULL, {});
    Image image;
    image.data = stbi_load(path, &image.size.x, &image.size.y, &image.channels, 4);
    return image;
}
