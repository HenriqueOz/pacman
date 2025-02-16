#ifndef WORLD_H
#define WORLD_H

#include "components/registry.hpp"
#include "game/input_manager.hpp"
#include <SDL3/SDL_render.h>

class World
{
  public:
    World(Registry & registry);

    void update(float delta_time, InputManager & input_manager);
    void render(SDL_Renderer * renderer);

  private:
    Registry _registry;
};

#endif
