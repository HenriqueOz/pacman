#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <vector>

#include <SDL3/SDL_render.h>

#include "game/input.hpp"
#include "entities/pacman.hpp"
#include "entities/pellet.hpp"

class World
{
  public:
    World() = default;
    ~World() = default;

    void initialize(SDL_Renderer * renderer, Input & input, CollisionManager & collision);
    void update(float deltaTime);
    void render(SDL_Renderer * renderer);
    void renderGui(SDL_Renderer * renderer);

  private:
    std::unique_ptr<Pacman> _pacman;
    std::vector<std::unique_ptr<Pellet>> _pellets;
};

#endif
