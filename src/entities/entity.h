#ifndef _ENTITY_H
#define _ENTITY_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <vec/vec.h>

enum EntityType
{
    PACMAN,
    GHOST,
    COLLIDER,
    CHERRY,
    FOOD,
    GUI
};

class Entity
{
  public:
    virtual ~Entity() {};
    virtual void update() {};
    virtual void render(SDL_Renderer *renderer, TTF_TextEngine *textEgine) const {};
    virtual void renderGUI(SDL_Renderer *renderer, TTF_TextEngine *textEgine) const {};

    virtual Vec2 getPosition() const { return m_position; };
    virtual Vec2 getSize() const { return m_size; };
    virtual EntityType getType() const = 0;

    void setId(Uint32 id);
    Uint32 getId();

  protected:
    Entity() {};

    Uint32 m_id = 0;
    bool m_idSet = false;

    Vec2 m_position = { 0, 0 };
    Vec2 m_size = { 0, 0 };
};

#endif
