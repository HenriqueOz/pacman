#ifndef WORLD_H
#define WORLD_H

#include <memory>

#include <SDL3/SDL_render.h>

#include "game/input.hpp"
#include "pure/pacman.hpp"

class World
{
  public:
    World();
    ~World() = default;

    void update(float deltaTima, Input & input);
    void render(SDL_Renderer * renderer);
    void renderGui(SDL_Renderer * renderer);

  private:
    std::unique_ptr<Pacman> _pacman;

    void initialize();
};

#endif
