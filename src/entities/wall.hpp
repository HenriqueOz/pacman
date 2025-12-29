#ifndef WALL_H_
#define WALL_H_

#include <SDL3/SDL_render.h>

#include "game/collision_manager.hpp"
#include "game/sprite.hpp"

class Wall
{
  public:
    Wall(float x, float y, SDL_Renderer * renderer, CollisionManager & collision);
    ~Wall();

    void update(float deltaTime);
    void render(SDL_Renderer * renderer) const;

  private:
    CollisionManager & _collision;

    Vec2<float> _position{};
    Vec2<int> _size{};
    Sprite _sprite;
    CollisionBox _bbox;
};

#endif