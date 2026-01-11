#ifndef GHOST_H_
#define GHOST_H_

#include <cstdint>
#include <memory>
#include <random>

#include "SDL3/SDL_render.h"

#include "game/collision_box.hpp"
#include "game/collision_manager.hpp"
#include "game/game_state.hpp"
#include "game/sprite.hpp"
#include "game/utils.hpp"

enum GhostType : std::uint8_t
{
    kBlinky
};

enum class GhostState : std::uint8_t
{
    kSpawing,
    kChasing,
    kScattered,
    kFrightened,
    kEaten,
    kEnteringSpawn
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

    void update(float deltaTime, const Vec2<float> pacmanPosition, GameState & gameState);
    void render(SDL_Renderer * renderer) const;

  private:
    CollisionManager & _collision;
    GhostType _type;
    GhostState _state{ GhostState::kSpawing };

    std::unique_ptr<Sprite> _normalSprite;
    std::unique_ptr<Sprite> _frightenedSprite;
    std::unique_ptr<Sprite> _eatenSprite;
    std::unique_ptr<CollisionBox> _bbox;

    std::random_device _rd;
    std::mt19937 _gen;
    std::uniform_int_distribution<int> _dist;

    Vec2<float> _spawnPosition{};
    Vec2<float> _exitPosition{};
    Vec2<float> _position{};
    Vec2<float> _doorPosition{};
    Vec2<float> _scatterPosition{};
    Vec2<int> _direction{};

    int _scatterDuration{ 30 };
    int _chaseDuration{ 120 };
    int _spawnDuration{ 120 };
    int _spawnTimer{ _spawnDuration };
    int _targetSwitchTimer{};
    bool _isDead{ false };
    float _baseSpeed{ 0.5f };
    float _eatenSpeed{ 1.0f };
    float _speed{ _baseSpeed };

    void update_chasing_state(GameState & gameState);

    void exit_spawn();
    void enter_spawn();

    void update_direction_to_target(const Vec2<float> targetPosition);
    void update_direction_randomly();

    void handle_state(const Vec2<float> pacmanPosition, GameState & gameState);
    void frightened_state(GameState & gameState);
    void eaten_state();

    std::vector<Vec2<int>> get_available_directions() const;
    bool is_direction_available(const Vec2<int> direction) const;

    CollisionTagBitMask get_collision_mask() const;
};

#endif