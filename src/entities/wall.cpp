#include "entities/wall.hpp"
#include "game/collision_box.hpp"
#include "game/utils.hpp"
#include <memory>

Wall::Wall(bool isGhostDoor, Vec2<float> position, SDL_Renderer * renderer, CollisionManager & collision)
  : _collision(collision)
  , _position(position)
  , _isGhostDoor(isGhostDoor)
{
    Vec2<int> bboxSize = { config::tile::kTileWidth, config::tile::kTileHeight };
    CollisionTagBit bboxTag = CollisionTagBit::kWall;

    if (_isGhostDoor) {
        bboxTag = CollisionTagBit::kGhostDoor;
        bboxSize.x = 2 * config::tile::kTileWidth;
    }

    _bbox = std::make_unique<CollisionBox>(_position, bboxSize, bboxTag);
    _collision.register_box(_bbox.get());
    _sprite = std::make_unique<Sprite>(_position, renderer, config::assets::kWallIdleSprite);
}

Wall::~Wall()
{
    _collision.unregister_box(_bbox.get());
}

void
Wall::render(SDL_Renderer * renderer) const
{
    if (!_isGhostDoor)
        _sprite->render(renderer);
}
