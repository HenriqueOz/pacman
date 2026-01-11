#include <array>
#include <cmath>
#include <filesystem>
#include <limits>
#include <memory>
#include <random>
#include <sal.h>
#include <vector>

#include <SDL3/SDL_log.h>
#include <SDL3/SDL_events.h>

#include "ghost.hpp"
#include "config/config.hpp"
#include "game/collision_box.hpp"
#include "game/collision_manager.hpp"
#include "game/game_state.hpp"
#include "game/utils.hpp"

const std::array<const std::filesystem::path, 1> sprites = { config::assets::kBlinkyIdleSprite };

inline Vec2<float>
get_ghost_scatter_position(GhostType type)
{
    switch (type) {
        case kBlinky:
            return tile_to_position({ config::tile::kHorizontalTiles, 0 });
            break;
    }
}

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
{
    _gen = std::mt19937(_rd());
    _dist = std::uniform_int_distribution<int>(1, 4);

    const Vec2<int> bboxSize = { config::tile::kTileWidth, config::tile::kTileHeight };

    _bbox = std::make_unique<CollisionBox>(_collision, _position, bboxSize, CollisionTagBit::kGhost);
    _normalSprite = std::make_unique<Sprite>(_position, renderer, sprites[_type]);
    _frightenedSprite = std::make_unique<Sprite>(_position, renderer, config::assets::kFrightenedIdleSprite);
    _eatenSprite = std::make_unique<Sprite>(_position, renderer, config::assets::kEatenIdleSprite);
    _scatterPosition = get_ghost_scatter_position(_type);
}

void
Ghost::update(float deltaTime, const Vec2<float> pacmanPosition, GameState & gameState)
{
    _position = wrap_position_by_size_around_screen(_position, { config::tile::kTileWidth, config::tile::kTileHeight });

    handle_state(pacmanPosition, gameState);

    float hspd = _speed * _direction.x;
    float vspd = _speed * _direction.y;

    if (hspd != 0) {
        const Vec2<float> checkPosition = { _position.x + hspd, _position.y };
        if (_collision.check_collision_at(checkPosition, _bbox->get_size(), get_collision_mask())) {
            hspd = 0;
        }
    }

    if (vspd != 0) {
        const Vec2<float> checktPosition = { _position.x, _position.y + vspd };
        if (_collision.check_collision_at(checktPosition, _bbox->get_size(), get_collision_mask())) {
            vspd = 0;
        }
    }

    _position = { _position.x + hspd, _position.y + vspd };

    _normalSprite->position = _position;
    _frightenedSprite->position = _position;
    _eatenSprite->position = _position;

    _collision.update_box_position(_bbox.get(), _position);
}

void
Ghost::render(SDL_Renderer * renderer) const
{
    switch (_state) {
        case GhostState::kSpawing:
        case GhostState::kChasing:
        case GhostState::kScattered:
            _normalSprite->render(renderer);
            break;
        case GhostState::kEnteringSpawn:
        case GhostState::kEaten:
            _eatenSprite->render(renderer);
            break;
        case GhostState::kFrightened:
            _frightenedSprite->render(renderer);
            break;
    }
}

void
Ghost::handle_state(const Vec2<float> pacmanPosition, GameState & gameState)
{
    switch (_state) {
        case GhostState::kSpawing:
            exit_spawn();
            break;
        case GhostState::kChasing:
            update_chasing_state(gameState);
            update_direction_to_target(pacmanPosition);
            break;
        case GhostState::kScattered:
            update_chasing_state(gameState);
            update_direction_to_target(_scatterPosition);
            break;
        case GhostState::kFrightened:
            frightened_state(gameState);
            break;
        case GhostState::kEaten:
            eaten_state();
            break;
        case GhostState::kEnteringSpawn:
            enter_spawn();
            break;
    }
}

void
Ghost::frightened_state(GameState & gameState)
{
    _state = gameState.are_ghosts_frightened() ? _state : GhostState::kChasing;
    update_direction_randomly();

    if (_collision.check_collision_at(
          _position, _bbox->get_size(), static_cast<CollisionTagBitMask>(CollisionTagBit::kPacman))) {
        _position = tile_to_position(position_to_tile(_position));
        _direction = { 0, 0 };
        _state = GhostState::kEaten;
    }
}

void
Ghost::eaten_state()
{
    _speed = _eatenSpeed;

    const Vec2<float> exitTarget = { _exitPosition.x, _exitPosition.y - config::tile::kTileHeight };
    if (dot_distance(_position, exitTarget) == 0.0f) {
        _speed = _baseSpeed;
        _direction = { 0, 0 };
        _position.x = _spawnPosition.x;
        _state = GhostState::kEnteringSpawn;
    } else {
        update_direction_to_target(exitTarget);
    }
}

void
Ghost::update_direction_randomly()
{
    const std::vector<Vec2<int>> & directions = get_available_directions();

    if (directions.empty()) {
        return;
    }

    _dist.param(std::uniform_int_distribution<int>::param_type(0, directions.size() - 1));

    int index = _dist(_gen);

    _direction = directions[index];
}

void
Ghost::exit_spawn()
{
    if (_spawnTimer-- > 0) {
        const float upBound = _spawnPosition.y - config::tile::kTileHeight;
        const float downBound = _spawnPosition.y + config::tile::kTileHeight;

        if (_position.y <= upBound) {
            _direction = { 0, 1 };
        } else if (_position.y >= downBound) {
            _direction = { 0, -1 };
        }
    } else {
        // TODO implement x direction choose
        const Vec2<float> exitTarget = { _exitPosition.x, _exitPosition.y - config::tile::kTileHeight };
        if (dot_distance(_position, exitTarget) > 4.0f) {
            _direction = { 0, -1 };
        } else {
            _direction = { -1, 0 };
            _state = GhostState::kChasing;
        }
    }
}

void
Ghost::enter_spawn()
{
    if (dot_distance(_position, _spawnPosition) > 0.0f) {
        _direction = { 0, 1 };
    } else {
        _spawnTimer = _spawnDuration;
        _state = GhostState::kSpawing;
    }
}

void
Ghost::update_chasing_state(GameState & gameState)
{
    if (gameState.are_ghosts_frightened()) {
        _state = GhostState::kFrightened;
        return;
    }

    if (_targetSwitchTimer-- <= 0) {
        switch (_state) {
            case GhostState::kChasing:
                _targetSwitchTimer = _scatterDuration;
                _state = GhostState::kScattered;
                break;
            case GhostState::kScattered:
                _targetSwitchTimer = _chaseDuration;
                _state = GhostState::kChasing;
                break;
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

    const std::vector<Vec2<int>> availableDirections = get_available_directions();

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

CollisionTagBitMask
Ghost::get_collision_mask() const
{
    const CollisionTagBit ghostDoorTag = _state == GhostState::kSpawing || _state == GhostState::kEnteringSpawn
                                           ? CollisionTagBit::kNone
                                           : CollisionTagBit::kGhostDoor;
    return CollisionTagBit::kWall | ghostDoorTag;
}

std::vector<Vec2<int>>
Ghost::get_available_directions() const
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

    return availableDirections;
}

bool
Ghost::is_direction_available(const Vec2<int> direction) const
{
    // TODO simplify logic
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

    const bool hasCollision = _collision.check_collision_at(nextPosition, _bbox->get_size(), get_collision_mask());

    return !hasCollision;
}