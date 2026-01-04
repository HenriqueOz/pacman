#include <SDL3/SDL_events.h>
#include <array>
#include <filesystem>
#include <limits>
#include <vector>

#include "ghost.hpp"
#include "config/config.hpp"
#include "game/utils.hpp"

const std::array<const std::filesystem::path, 1> sprites = { config::assets::kBlinkyIdleSprite };

Ghost::Ghost(GhostType type,
             Vec2<float> position,
             Vec2<float> exitPosition,
             SDL_Renderer * renderer,
             CollisionManager & collision)
  : _position(position)
  , _spawnPosition(position)
  , _exitPosition(exitPosition)
  , _direction({ 0, 1 })
  , _type(type)
  , _collision(collision)
  , _previousTile(position_to_tile(position))
  , _tile(position_to_tile(position))
  , _bbox(_position, { config::tile::kTileWidth, config::tile::kTileHeight }, CollisionTag::ghost)
  , _sprite(_position, renderer, sprites[type])
{
    _collision.register_box(&_bbox);
}

void
Ghost::update(float deltaTime, const Vec2<float> pacmanPosition)
{
    update_direction(pacmanPosition);

    float hspd = _speed * _direction.x;
    float vspd = _speed * _direction.y;

    _position = { _position.x + hspd, _position.y + vspd };
    _sprite.position = _position;
    _collision.update_box_position(&_bbox, _position);

    _previousTile = _tile;
    _tile = position_to_tile(_position);
}

void
Ghost::render(SDL_Renderer * renderer) const
{
    _sprite.render(renderer);
}

Vec2<float>
Ghost::get_target(const Vec2<float> pacmanPosition)
{
    if (_isDead) {
        return _spawnPosition;
    }

    // if (!(_hasExitedSpawn = dot_distance(_position, _exitPosition) == 0.0f)) {
    //     return _exitPosition;
    // }

    return pacmanPosition;
}

void
Ghost::update_direction(const Vec2<float> targetPosition)
{
    const std::array<Vec2<int>, 4> directions = {
        Vec2(0, -1),
        Vec2(-1, 0),
        Vec2(0, 1),
        Vec2(1, 0),
    };
    std::vector<Vec2<int>> availableDirections{};
    availableDirections.reserve(4);

    for (const Vec2<int> d : directions) {
        if (is_direction_available(d)) {
            availableDirections.push_back(d);
        }
    }

    float shortestDistance = std::numeric_limits<float>::max();
    Vec2<int> newDirection = _direction;

    for (const Vec2<int> d : availableDirections) {
        const float distance = dot_distance({ _position.x + d.x, _position.y + d.y }, targetPosition);
        if (distance < shortestDistance) {
            shortestDistance = distance;
            newDirection = d;
        }
    }

    _direction = newDirection;
}

bool
Ghost::is_direction_available(const Vec2<int> direction) const
{
    const Vec2<float> targetPosition = { _position.x + direction.x * _speed, _position.y + direction.y * _speed };
    const bool hasWall = _collision.check_collision_at(targetPosition, _bbox.size, CollisionTag::wall);

    const bool isReverseX = (_direction.x == 1 && direction.x == -1) || (_direction.x == -1 && direction.x == 1);
    const bool isReverseY = (_direction.y == 1 && direction.y == -1) || (_direction.y == -1 && direction.y == 1);

    return !hasWall && !isReverseX && !isReverseY;
}