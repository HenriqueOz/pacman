#ifndef WORLD_H
#define WORLD_H

#include <SDL3/SDL_render.h>
#include <memory>
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
    void update(float deltaTime, Input & input, CollisionManager & collision);
    void render(SDL_Renderer * renderer);
    void renderGui(SDL_Renderer * renderer);

  private:
    std::unique_ptr<Pacman> _pacman;
    std::vector<std::unique_ptr<Pellet>> _pellets;
};

#endif
