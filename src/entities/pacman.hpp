#ifndef PACMAN_H_
#define PACMAN_H_

#include <memory>

#include <SDL3/SDL_render.h>

#include "game/input.hpp"
#include "game/collision_box.hpp"
#include "game/collision_manager.hpp"
#include "game/sprite.hpp"
#include "game/utils.hpp"

class Pacman
{
  public:
    Pacman(Vec2<float> position, SDL_Renderer * renderer, Input & input, CollisionManager & collision);
    ~Pacman();

    void update(float deltaTime);
    void render(SDL_Renderer * renderer);

    const Vec2<float> & get_position() const { return _position; }
    const Vec2<int> & get_direction() const { return _direction; }

  private:
    CollisionManager & _collision;
    Input & _input;

    std::unique_ptr<Sprite> _sprite;
    std::unique_ptr<CollisionBox> _bbox;

    Vec2<float> _position{};
    Vec2<int> _direction{};

    float _baseSpeed = 0.5f;
    float _speed = _baseSpeed;

    void update_direction(Input & input);
    void wrap_around_screen();
    CollisionTagBitMask get_collision_mask() const;
};

#endif
