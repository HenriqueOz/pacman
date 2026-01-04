#include "entities/wall.hpp"
#include "config/config.hpp"
#include "game/utils.hpp"

Wall::Wall(Vec2<float> position, SDL_Renderer * renderer, CollisionManager & collision)
  : _collision(collision)
  , _position(position)
  , _bbox(_position, { config::tile::kTileWidth, config::tile::kTileHeight }, CollisionTag::wall)
  , _sprite(_position, renderer, config::assets::kWallIdleSprite)
{
    collision.register_box(&_bbox);
}

Wall::~Wall()
{
    _collision.unregister_box(&_bbox);
}

void
Wall::render(SDL_Renderer * renderer) const
{
    _sprite.render(renderer);
}
