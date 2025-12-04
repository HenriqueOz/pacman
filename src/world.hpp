#ifndef WORLD_H
#define WORLD_H

#include "ecs/registry.hpp"
#include "game/input_manager.hpp"
#include <SDL3/SDL_render.h>

class World
{
  public:
    World(ecs::Registry & registry);

    void update(float deltaTima, InputManager & inputManager);
    void render(SDL_Renderer * renderer);
    void renderGui(SDL_Renderer * renderer);

  private:
    ecs::Registry _registry;

    void initialize();
};

#endif
