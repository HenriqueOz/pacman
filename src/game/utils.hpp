#ifndef UTILS_H_
#define UTILS_H_

#include <cmath>

#include "SDL3/SDL_render.h"

#include "config/config.hpp"

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

inline int
sign(int value)
{
    return (value > 0) - (value < 0);
}

inline Vec2<float>
tile_to_position(Vec2<int> tile)
{
    return { static_cast<float>(tile.x * config::tile::kTileWidth),
             static_cast<float>(tile.y * config::tile::kTileHeight) };
}

inline Vec2<int>
position_to_tile(Vec2<float> position)
{
    return { static_cast<int>(position.x / config::tile::kTileWidth),
             static_cast<int>(position.y / config::tile::kTileHeight) };
}

inline Vec2<float>
wrap_position_by_size_around_screen(const Vec2<float> position, const Vec2<int> size)
{
    Vec2<float> newPos = position;

    if (position.x + size.x < 0) {
        newPos.x = static_cast<float>(config::view::kGameTextureWidth);
    } else if (position.x > static_cast<float>(config::view::kGameTextureWidth)) {
        newPos.x = -size.x;
    }

    if (position.y + size.y < 0) {
        newPos.y = static_cast<float>(config::view::kGameTextureHeight);
    } else if (position.y > static_cast<float>(config::view::kGameTextureHeight)) {
        newPos.y = -size.y;
    }

    return newPos;
}

inline float
dot_distance(Vec2<float> p1, Vec2<float> p2)
{
    return std::sqrt(std::pow(p2.x - p1.x, 2.0f) + std::pow(p2.y - p1.y, 2.0f));
}

#endif
