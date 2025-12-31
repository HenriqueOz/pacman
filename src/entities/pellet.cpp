#include "SDL3/SDL_render.h"

#include "config/config.hpp"
#include "game/utils.hpp"
#include "pellet.hpp"

Pellet::Pellet(Vec2<float> position, SDL_Renderer * renderer, CollisionManager & collision)
  : _collision(collision)
  , _position(position)
  , _bbox({ _position.x + config::tile::kTileWidth / 2.0f, position.y + config::tile::kTileHeight / 2.0f },
          { config::tile::kTileWidth / 4, config::tile::kTileHeight / 4 },
          CollisionTag::pellet)
  , _sprite(_position, renderer, config::assets::kPelletIdleSprite)
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
