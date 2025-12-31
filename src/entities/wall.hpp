#ifndef WALL_H_
#define WALL_H_

#include <SDL3/SDL_render.h>

#include "game/collision_manager.hpp"
#include "game/sprite.hpp"
#include "game/utils.hpp"

class Wall
{
  public:
    Wall(Vec2<float> position, SDL_Renderer * renderer, CollisionManager & collision);
    ~Wall();

    void update(float deltaTime);
    void render(SDL_Renderer * renderer) const;

  private:
    CollisionManager & _collision;

    Vec2<float> _position{};
    Sprite _sprite;
    CollisionBox _bbox;
};

#endif