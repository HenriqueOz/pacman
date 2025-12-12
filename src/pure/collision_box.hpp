#ifndef COLLISION_H_
#define COLLISION_H_

#include <cstdint>

#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_render.h"
#include "pure/utils.hpp"

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

    CollisionBox(const Vec2<float> position,
                 const Vec2<int> size,
                 const CollisionTag tag);

    ~CollisionBox() = default;

    inline const Vec2<float> get_old_position() const { return _oldPosition; };
    inline const Vec2<float> get_position() const { return _position; };
    inline CollisionTag get_tag() const { return _tag; };

    inline void update_position(const Vec2<float> newPosition)
    {
        _oldPosition = _position;
        _position = newPosition;
    }

    void render(SDL_Renderer * renderer, SDL_Color && color) const;

  private:
    Vec2<float> _oldPosition;
    Vec2<float> _position;
    CollisionTag _tag;
};

#endif
