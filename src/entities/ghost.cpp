#include <SDL3/SDL_log.h>
#include <array>
#include <cmath>
#include <filesystem>
#include <limits>
#include <vector>

#include <SDL3/SDL_events.h>

#include "ghost.hpp"
#include "config/config.hpp"
#include "game/collision_box.hpp"
#include "game/collision_manager.hpp"
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
  , _bbox(position, { config::tile::kTileWidth, config::tile::kTileHeight }, CollisionTag::ghost)
  , _sprite(position, renderer, sprites[type])
{
    _collision.register_box(&_bbox);
}

void
Ghost::update(float deltaTime, const Vec2<float> pacmanPosition)
{
    _position = wrap_position_by_size_around_screen(_position, { config::tile::kTileWidth, config::tile::kTileHeight });

    if (!_hasExitedSpawn) {
        exit_spawn();
    } else {
        update_direction_to_target(get_target(pacmanPosition));
    }

    float hspd = _speed * _direction.x;
    float vspd = _speed * _direction.y;

    if (hspd != 0) {
        if (_collision.check_collision_at({ _position.x + hspd, _position.y }, _bbox.size, CollisionTag::wall) ||
            (_hasExitedSpawn &&
             _collision.check_collision_at({ _position.x + hspd, _position.y }, _bbox.size, CollisionTag::ghostDoor))) {
            hspd = 0;
        }
    }

    if (vspd != 0) {
        if (_collision.check_collision_at({ _position.x, _position.y + vspd }, _bbox.size, CollisionTag::wall) ||
            (_hasExitedSpawn &&
             _collision.check_collision_at({ _position.x, _position.y + vspd }, _bbox.size, CollisionTag::ghostDoor))) {
            vspd = 0;
        }
    }

    _position = { _position.x + hspd, _position.y + vspd };

    _sprite.position = _position;
    _collision.update_box_position(&_bbox, _position);
}

void
Ghost::render(SDL_Renderer * renderer) const
{
    _sprite.render(renderer);
}

Vec2<float>
Ghost::get_target(const Vec2<float> pacmanPosition)
{
    return pacmanPosition;
}

void
Ghost::exit_spawn()
{
    if (_spawnCooldown > 0) {
        _spawnCooldown--;
        const float upBound = _spawnPosition.y - config::tile::kTileHeight;
        const float downBound = _spawnPosition.y + config::tile::kTileHeight;

        if (_position.y <= upBound) {
            _direction = { 0, 1 };
        } else if (_position.y >= downBound) {
            _direction = { 0, -1 };
        }
    } else {
        const Vec2<float> exitTarget = { _exitPosition.x, _exitPosition.y - config::tile::kTileHeight };
        if (dot_distance(_position, exitTarget) > 4.0f) {
            _direction = { 0, -1 };
        } else {
            _direction = { -1, 0 };
            _hasExitedSpawn = true;
        }
    }
}

void
Ghost::update_direction_to_target(const Vec2<float> targetPosition)
{
    // Ignore when out of the map in the x axis
    if (_position.x <= 0 || _position.x >= config::view::kGameTextureWidth) {
        return;
    }

    const std::array<Vec2<int>, 4> directions = {
        Vec2(0, -1), // up
        Vec2(-1, 0), // left
        Vec2(0, 1),  // down
        Vec2(1, 0),  // right
    };
    std::vector<Vec2<int>> availableDirections{};
    availableDirections.reserve(4);

    for (const Vec2<int> d : directions) {
        if (is_direction_available(d)) {
            availableDirections.push_back(d);
        }
    }

    if (availableDirections.empty()) {
        return;
    }

    float shortestDistance = std::numeric_limits<float>::max();
    Vec2<int> newDirection = _direction;

    for (const Vec2<int> d : availableDirections) {
        const Vec2<float> nextPosition = { _position.x + _speed * d.x, _position.y + _speed * d.y };
        const float distance = dot_distance(nextPosition, targetPosition);
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
    const bool isReverseX = (_direction.x == 1 && direction.x == -1) || (_direction.x == -1 && direction.x == 1);
    const bool isReverseY = (_direction.y == 1 && direction.y == -1) || (_direction.y == -1 && direction.y == 1);

    if (isReverseX || isReverseY) {
        return false;
    }

    const int x = static_cast<int>(std::round(_position.x));
    const int y = static_cast<int>(std::round(_position.y));

    if (x % config::tile::kTileWidth != 0 || y % config::tile::kTileHeight != 0) {
        return false;
    }

    Vec2<float> nextPosition = { _position.x + direction.x, _position.y + direction.y };

    const bool hasWall = _collision.check_collision_at(nextPosition, _bbox.size, CollisionTag::wall);
    const bool hasGhostDoor =
      !_hasExitedSpawn ? false : _collision.check_collision_at(nextPosition, _bbox.size, CollisionTag::ghostDoor);

    return !hasWall && !hasGhostDoor;
}