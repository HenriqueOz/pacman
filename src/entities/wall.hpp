#ifndef WALL_H_
#define WALL_H_

#include <SDL3/SDL_render.h>
#include <memory>

#include "game/collision_manager.hpp"
#include "game/sprite.hpp"
#include "game/utils.hpp"

class Wall
{
  public:
    Wall(bool isGhostDoor, Vec2<float> position, SDL_Renderer * renderer, CollisionManager & collision);
    ~Wall();

    void render(SDL_Renderer * renderer) const;

  private:
    CollisionManager & _collision;

    std::unique_ptr<Sprite> _sprite;
    std::unique_ptr<CollisionBox> _bbox;

    Vec2<float> _position{};

    bool _isGhostDoor;
};

#endif