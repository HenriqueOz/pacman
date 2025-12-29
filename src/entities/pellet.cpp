#include "SDL3/SDL_render.h"

#include "config/config.hpp"
#include "pellet.hpp"

Pellet::Pellet(float x, float y, SDL_Renderer * renderer, CollisionManager & collision)
  : _collision(collision)
  , _position{ x, y }
  , _size{ 8, 8 }
  , _bbox({ x + _size.x, y + _size.y }, _size, CollisionTag::pellet)
  , _sprite({ x + _size.x, y + _size.y }, _size, renderer, config::assets::kPelletIdleSprite)
{
    collision.register_box(&_bbox);
}

Pellet::~Pellet()
{
    _collision.unregister_box(&_bbox);
}

void
Pellet::update(float deltaTime)
{
    if (_eaten) {
        return;
    }

    _eaten = _collision.check_collision_at(_bbox.position, _bbox.size, CollisionTag::pacman);
}

void
Pellet::render(SDL_Renderer * renderer) const
{
    if (_eaten) {
        return;
    }

    _sprite.render(renderer);
}
