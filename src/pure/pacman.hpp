#ifndef PACMAN_H_
#define PACMAN_H_

#include <SDL3/SDL_render.h>

#include "game/input.hpp"
#include "pure/collision_box.hpp"
#include "pure/collision_manager.hpp"
#include "pure/sprite.hpp"
#include "utils.hpp"

class Pacman
{
  public:
    Pacman(float x,
           float y,
           SDL_Renderer * renderer,
           Input & input,
           CollisionManager & collision);
    ~Pacman() = default;

    void update(float deltaTime);
    void render(SDL_Renderer * renderer);

    const Vec2<float> & get_position() const { return _position; }
    const Vec2<int> & get_direction() const { return _direction; }

  private:
    CollisionManager & _collision;
    Input & _input;

    Vec2<float> _position{};
    Vec2<int> _direction{};
    Sprite _sprite;
    CollisionBox _bbox;
    float _speed = 60.0f;

    void update_direction(Input & input);
};

#endif
