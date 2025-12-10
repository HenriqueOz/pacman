#ifndef PELLET_H_
#define PELLET_H_

#include <SDL3/SDL_render.h>

#include "game/input.hpp"
#include "pure/sprite.hpp"
#include "utils.hpp"

class Pellet
{
  public:
    Pellet() = default;
    ~Pellet() = default;

    void initialize(float x, float y, SDL_Renderer * renderer);
    void update(float deltaTime, Input & input);
    void render(SDL_Renderer * renderer);

    const Vec2<float> & get_position() const { return _position; }

  private:
    Vec2<float> _position{};
    Sprite _sprite;

    void update_direction(Input & input);
};

#endif