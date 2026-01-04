#ifndef GHOST_H_
#define GHOST_H_

#include <cstdint>

#include <SDL3/SDL_render.h>

#include "game/collision_manager.hpp"
#include "game/sprite.hpp"
#include "game/utils.hpp"

enum GhostType : std::uint8_t
{
    kBlinky
};

class Ghost
{
  public:
    Ghost(GhostType type,
          Vec2<float> position,
          Vec2<float> exitPosition,
          SDL_Renderer * renderer,
          CollisionManager & collision);
    ~Ghost() = default;

    void update(float deltaTime, const Vec2<float> pacmanPosition);
    void render(SDL_Renderer * renderer) const;

  private:
    CollisionManager & _collision;
    GhostType _type;
    Vec2<float> _spawnPosition{};
    Vec2<float> _exitPosition{};
    Vec2<float> _position{};
    Vec2<float> _doorPosition{};
    Vec2<int> _previousTile{};
    Vec2<int> _direction{};
    Sprite _sprite;
    CollisionBox _bbox;

    int _spawnCooldown{ 120 };
    bool _hasExitedSpawn = false;
    bool _isDead = false;
    float _baseSpeed = 0.5f;
    float _speed = _baseSpeed;

    void update_direction_to_target(const Vec2<float> targetPosition);
    void exit_spawn();
    Vec2<float> get_target(const Vec2<float> pacmanPosition);
    bool is_direction_available(const Vec2<int> direction) const;
};

#endif