#include <SDL3/SDL_events.h>
#include <array>
#include <filesystem>
#include <limits>
#include <vector>

#include "ghost.hpp"
#include "config/config.hpp"
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
  , _previousTile(position_to_tile(position))
  , _bbox(_position, { config::tile::kTileWidth, config::tile::kTileHeight }, CollisionTag::ghost)
  , _sprite(_position, renderer, sprites[type])
{
    _collision.register_box(&_bbox);
}

void
Ghost::update(float deltaTime, const Vec2<float> pacmanPosition)
{
    const Vec2<float> entityCenter = { _position.x + config::tile::kTileWidth / 2.0f,
                                       _position.y + config::tile::kTileHeight / 2.0f };
    const Vec2<int> currentTile = position_to_tile(entityCenter);

    if (!_hasExitedSpawn) {
        exit_spawn();
    } else if (!currentTile.is_equal(_previousTile)) {
        update_direction_to_target(get_target(pacmanPosition));
        _previousTile = currentTile;
    }

    float hspd = _speed * _direction.x;
    float vspd = _speed * _direction.y;

    _position = { _position.x + hspd, _position.y + vspd };
    _position = wrap_position_by_size_around_screen(_position, { config::tile::kTileWidth, config::tile::kTileHeight });

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
        if (dot_distance(_position, exitTarget) > 0.0f) {
            _direction = { 0, -1 };
        } else {
            _hasExitedSpawn = true;
        }
    }
}

void
Ghost::update_direction_to_target(const Vec2<float> targetPosition)
{
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

    const Vec2<float> entityCenter = { _position.x + config::tile::kTileWidth / 2.0f,
                                       _position.y + config::tile::kTileHeight / 2.0f };
    const Vec2<int> currentTile = position_to_tile(entityCenter);

    for (const Vec2<int> d : availableDirections) {
        const Vec2<int> nextTile = { currentTile.x + d.x, currentTile.y + d.y };
        const Vec2<float> nextTileTopLeft = tile_to_position(nextTile);
        const Vec2<float> nextTileCenter = { nextTileTopLeft.x + config::tile::kTileWidth / 2.0f,
                                             nextTileTopLeft.y + config::tile::kTileHeight / 2.0f };
        const float distance = dot_distance(nextTileCenter, targetPosition);
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
    const Vec2<float> entityCenter = { _position.x + config::tile::kTileWidth / 2.0f,
                                       _position.y + config::tile::kTileHeight / 2.0f };
    const Vec2<int> currentTile = position_to_tile(entityCenter);
    const Vec2<int> nextTile = { currentTile.x + direction.x, currentTile.y + direction.y };
    const Vec2<float> nextTileTopLeft = tile_to_position(nextTile);

    const Vec2<float> nextTileCenter = { nextTileTopLeft.x + config::tile::kTileWidth / 2.0f,
                                         nextTileTopLeft.y + config::tile::kTileHeight / 2.0f };

    const bool hasWall = _collision.check_collision_at(nextTileCenter, { 1, 1 }, CollisionTag::wall);

    const bool isReverseX = (_direction.x == 1 && direction.x == -1) || (_direction.x == -1 && direction.x == 1);
    const bool isReverseY = (_direction.y == 1 && direction.y == -1) || (_direction.y == -1 && direction.y == 1);

    return !hasWall && !isReverseX && !isReverseY;
}