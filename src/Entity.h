#ifndef _ENTITY_H
#define _ENTITY_H

#include "vec.h"
#include <SDL3/SDL.h>

enum EntityType
{
    PACMAN,
    GHOST,
    COLLIDER,
    CHERRY,
    FOOD
};

class Entity
{
  public:
    virtual ~Entity(){};
    virtual void update() = 0;
    virtual void render(SDL_Renderer *renderer) const {};
    virtual EntityType getType() const = 0;

  protected:
    Entity(){};

    Vec2 m_position = { 0.f, 0.f };
    Vec2 m_size = { 0.f, 0.f };
};

#endif
