#ifndef _ENTITY_H
#define _ENTITY_H

#include <SDL3/SDL.h>
#include <vec/vec.h>

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
    virtual ~Entity() {};
    virtual void update() = 0;
    virtual void render(SDL_Renderer *renderer) const {};

    virtual Vec2 getPosition() const { return m_position; };
    virtual Vec2 getSize() const { return m_size; };
    virtual EntityType getType() const = 0;

  protected:
    Entity() {};

    Vec2 m_position = { 0, 0 };
    Vec2 m_size = { 0, 0 };
};

#endif
