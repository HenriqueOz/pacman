#ifndef COLLISION_H_
#define COLLISION_H_

#include <cstdint>

#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_render.h"

#include "game/utils.hpp"

enum CollisionTag : std::uint8_t
{
    pacman = 1,
    ghost = 2,
    pellet = 3,
    wall = 4
};

class CollisionBox
{
  public:
    Vec2<int> size;
    Vec2<float> position;
    CollisionTag tag;

    CollisionBox(const Vec2<float> position, const Vec2<int> size, const CollisionTag tag);

    ~CollisionBox() = default;

    void render(SDL_Renderer * renderer, SDL_Color && color) const;
};

#endif
