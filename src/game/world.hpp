#ifndef WORLD_H
#define WORLD_H

#include <SDL3/SDL_render.h>
#include <vector>

#include "game/input.hpp"
#include "pure/pacman.hpp"
#include "pure/pellet.hpp"

class World
{
  public:
    World() = default;
    ~World() = default;

    void initialize(SDL_Renderer * renderer);
    void update(float deltaTime, Input & input);
    void render(SDL_Renderer * renderer);
    void renderGui(SDL_Renderer * renderer);

  private:
    Pacman _pacman;
    std::vector<Pellet> _pellets;
};

#endif
