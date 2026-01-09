#ifndef COLLISION_H_
#define COLLISION_H_

#include <cstdint>

#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_render.h"

#include "game/utils.hpp"

class CollisionManager;

enum class CollisionTagBit : std::uint8_t
{
    kNone = 0,
    kPacman = 1 << 0,
    kGhost = 1 << 1,
    kPellet = 1 << 2,
    kWall = 1 << 3,
    kGhostDoor = 1 << 4
};

using CollisionTagBitMask = std::uint8_t;

inline CollisionTagBitMask
operator&(CollisionTagBit l, CollisionTagBit r)
{
    return static_cast<CollisionTagBitMask>(l) & static_cast<CollisionTagBitMask>(r);
}

inline CollisionTagBitMask
operator|(CollisionTagBit l, CollisionTagBit r)
{
    return static_cast<CollisionTagBitMask>(l) | static_cast<CollisionTagBitMask>(r);
}

class CollisionBox
{
  public:
    Vec2<float> position;

    CollisionBox(CollisionManager & collision,
                 const Vec2<float> position,
                 const Vec2<int> size,
                 const CollisionTagBit tag);
    ~CollisionBox();

    void render(SDL_Renderer * renderer, SDL_Color && color) const;

    inline Vec2<int> get_size() const { return _size; };
    inline CollisionTagBitMask get_tag_mask() const { return static_cast<CollisionTagBitMask>(_tag); };

  private:
    CollisionManager & _collision;
    const Vec2<int> _size;
    const CollisionTagBit _tag;
};

#endif
