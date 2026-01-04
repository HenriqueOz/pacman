#ifndef ENTITY_H_
#define ENTITY_H_

#include <SDL3/SDL_render.h>

class IEntity
{
  public:
    IEntity() = default;
    virtual ~IEntity() = default;

    virtual void update(float deltaTime);
    virtual void render(SDL_Renderer * renderer);
};

#endif