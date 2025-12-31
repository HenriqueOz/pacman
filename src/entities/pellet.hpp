#ifndef PELLET_H_
#define PELLET_H_

#include <SDL3/SDL_render.h>

#include "game/collision_box.hpp"
#include "game/collision_manager.hpp"
#include "game/sprite.hpp"
#include "game/utils.hpp"

class Pellet
{
  public:
    Pellet(Vec2<float> position, SDL_Renderer * renderer, CollisionManager & collision);
    ~Pellet();

    void update(float deltaTime);
    void render(SDL_Renderer * renderer) const;

    const Vec2<float> & get_position() const { return _position; }

  private:
    CollisionManager & _collision;

    Vec2<float> _position{};
    Sprite _sprite;
    CollisionBox _bbox;

    bool _eaten = false;
};

#endif