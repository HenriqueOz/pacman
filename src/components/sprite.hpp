#ifndef SPRITE_H
#define SPRITE_H

#include <cstddef>
#include <string>
#include <sys/types.h>

class Sprite
{
  public:
    float x;
    float y;
    std::size_t width;
    std::size_t height;
    std::string filePath;
    std::size_t index;
    int xscale;
    int yscale;
};
#endif
