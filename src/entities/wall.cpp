#include "entities/wall.hpp"
#include "config/config.hpp"

Wall::Wall(float x, float y, SDL_Renderer * renderer, CollisionManager & collision)
  : _collision(collision)
  , _position{ x, y }
  , _size{ 16, 16 }
  , _bbox(_position, _size, CollisionTag::wall)
  , _sprite(_position, _size, renderer, config::assets::kWallIdleSprite)
{
    collision.register_box(&_bbox);
}

Wall::~Wall()
{
    _collision.unregister_box(&_bbox);
}

void
Wall::update(float deltaTime)
{

}

void
Wall::render(SDL_Renderer * renderer) const
{
    _sprite.render(renderer);
}
