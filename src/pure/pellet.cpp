#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"

#include "config/config.hpp"
#include "pellet.hpp"

Pellet::Pellet(float x,
               float y,
               SDL_Renderer * renderer,
               CollisionManager & collision)
  : _collision(collision)
  , _position{ x, y }
  , _size{ 8, 8 }
  , _bbox({ x + _size.x, y + _size.y }, _size, CollisionTag::pellet)
  , _sprite({ x + _size.x, y + _size.y },
            _size,
            renderer,
            config::assets::kPelletIdleSprite)
{
    collision.register_box(&_bbox);
}

Pellet::~Pellet()
{
    _collision.unregister_box(&_bbox);
    SDL_Log("Deleted");
}

void
Pellet::update(float deltaTime)
{
    _collected = _collision.check_collision_at(
      _bbox.position, _bbox.size, CollisionTag::pacman);

    if (_collected) {
        mark_to_delete();
    }
}

void
Pellet::render(SDL_Renderer * renderer) const
{
    _sprite.render(renderer);
    if (_collected) {
        _bbox.render(renderer, SDL_Color{ 0, 255, 0, 255 });
    }
}
