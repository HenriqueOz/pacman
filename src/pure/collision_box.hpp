#ifndef COLLISION_H_
#define COLLISION_H_

#include <cstdint>

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

    CollisionBox(const Vec2<float> position,
                 const Vec2<int> size,
                 const Tag tag);

    ~CollisionBox() = default;

    inline const Vec2<float> & get_old_position() const
    {
        return _oldPosition;
    };
    inline const Vec2<float> & get_position() const { return _position; };
    inline Tag get_tag() const { return _tag; };

    inline void update_position(const Vec2<float> newPosition)
    {
        _oldPosition = _position;
        _position = newPosition;
    }

    void render(SDL_Renderer * renderer, SDL_Color && color) const;

  private:
    Vec2<float> _oldPosition;
    Vec2<float> _position;
    Tag _tag;
};

#endif
