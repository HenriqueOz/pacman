#ifndef UTILS_H_
#define UTILS_H_

#include "SDL3/SDL_render.h"

template<typename T>
struct Vec2
{
    T x;
    T y;

    bool is_equal(const Vec2<T> & other) const { return (this->x == other.x && this->y == other.y); }
};

inline Vec2<int>
get_texture_size(SDL_Texture * t)
{
    float w, h;
    SDL_GetTextureSize(t, &w, &h);
    return { static_cast<int>(w), static_cast<int>(h) };
}

#endif
