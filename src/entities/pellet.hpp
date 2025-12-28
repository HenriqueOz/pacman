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
    Pellet(float x, float y, SDL_Renderer * renderer, CollisionManager & collision);
    ~Pellet();

    void update(float deltaTime);
    void render(SDL_Renderer * renderer) const;
    inline bool is_marked_to_delete() const { return _markedToDelete; }

    const Vec2<float> & get_position() const { return _position; }

  private:
    CollisionManager & _collision;

    Vec2<float> _position{};
    Vec2<int> _size;
    Sprite _sprite;
    CollisionBox _bbox;

    bool _markedToDelete = false;

    inline void mark_to_delete() { _markedToDelete = true; }

    bool _collected = false;
};

#endif