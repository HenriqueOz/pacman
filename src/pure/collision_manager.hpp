#ifndef COLLISION_MANAGER_H_
#define COLLISION_MANAGER_H_

#include <cstdint>
#include <vector>

#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_render.h"
#include "pure/utils.hpp"

using Tag = std::uint8_t;

const Tag pacman = 0x1;
const Tag ghost = 0x2;
const Tag pellet = 0x4;
const Tag wall = 0x8;

class CollisionBox
{
  public:
    Vec2<int> size;

    inline const Vec2<float> & get_old_position() { return _oldPosition; };
    inline const Vec2<float> & get_position() { return _position; };

    inline void update_position(const Vec2<float> newPosition)
    {
        _oldPosition = _position;
        _position = newPosition;
    }

    inline void render(SDL_Renderer * renderer, SDL_Color && color) const
    {
        const SDL_FRect rect = { .x = _position.x,
                                 .y = _position.y,
                                 .w = static_cast<float>(size.x),
                                 .h = static_cast<float>(size.y) };

        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 127);
        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }

  private:
    Vec2<float> _oldPosition;
    Vec2<float> _position;
    Tag _tag;
};

class CollisionManager
{
  public:
    CollisionManager(std::vector<std::vector<std::uint8_t>> & _grid);

    inline void update_box_on_map(const CollisionBox & box) {}

  private:
    std::vector<std::vector<std::uint8_t>> _grid;
};

#endif
