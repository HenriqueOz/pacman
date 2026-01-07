#include "entities/wall.hpp"
#include "game/collision_box.hpp"

Wall::Wall(bool isGhostDoor, Vec2<float> position, SDL_Renderer * renderer, CollisionManager & collision)
  : _collision(collision)
  , _position(position)
  , _isGhostDoor(isGhostDoor)
  , _bbox(_position, { config::tile::kTileWidth, config::tile::kTileHeight }, CollisionTag::wall)
  , _sprite(_position, renderer, config::assets::kWallIdleSprite)
{
    if (_isGhostDoor) {
        _bbox.tag = CollisionTag::ghostDoor;
        _bbox.size.x = 2 * config::tile::kTileWidth;
    }

    collision.register_box(&_bbox);
}

Wall::~Wall()
{
    _collision.unregister_box(&_bbox);
}

void
Wall::render(SDL_Renderer * renderer) const
{
    if (!_isGhostDoor)
        _sprite.render(renderer);

    _bbox.render(renderer, { 255, 0, 0, 255 });
}
