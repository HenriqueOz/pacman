#ifndef PELLET_H_
#define PELLET_H_

#include <SDL3/SDL_render.h>
#include <cstdint>
#include <filesystem>
#include <memory>

#include "game/collision_box.hpp"
#include "game/collision_manager.hpp"
#include "game/game_state.hpp"
#include "game/sprite.hpp"
#include "game/utils.hpp"

enum PelletType : std::uint8_t
{
    kNormal,
    kSuper,
    kFruit
};

class Pellet
{
  public:
    Pellet(PelletType type, Vec2<float> position, SDL_Renderer * renderer, CollisionManager & collision);
    ~Pellet();

    void update(float deltaTime, GameState & gameState);
    void render(SDL_Renderer * renderer) const;

    const Vec2<float> & get_position() const { return _position; }

  private:
    CollisionManager & _collision;

    std::unique_ptr<Sprite> _sprite;
    std::unique_ptr<CollisionBox> _bbox;

    PelletType _type;
    Vec2<float> _position{};

    bool _eaten = false;
    int _value = 10;

    std::filesystem::path get_sprite_path() const;
    void handle_eaten_event(GameState & gameState);
};

#endif