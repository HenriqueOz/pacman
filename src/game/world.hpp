#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <vector>

#include <SDL3/SDL_render.h>

#include "entities/ghost.hpp"
#include "entities/gui.hpp"
#include "entities/pacman.hpp"
#include "entities/pellet.hpp"
#include "entities/wall.hpp"
#include "game/collision_manager.hpp"
#include "game/input.hpp"
#include "game/map.hpp"
#include "game_state.hpp"

class World
{
  public:
    World(Map & map)
      : _map(map) {};
    ~World() = default;

    void initialize(SDL_Renderer * renderer, Input & input, CollisionManager & collision);
    void reset(SDL_Renderer * renderer, Input & input, CollisionManager & collision);
    void update(float deltaTime);
    void render(SDL_Renderer * renderer);
    void renderGui(SDL_Renderer * renderer);

    inline const GameState & get_game_state() const { return _gameState; };

  private:
    GameState _gameState;

    std::unique_ptr<Gui> _gui;
    std::unique_ptr<Pacman> _pacman;
    std::vector<std::unique_ptr<Pellet>> _pellets;
    std::vector<std::unique_ptr<Wall>> _walls;
    std::vector<std::unique_ptr<Ghost>> _ghosts;

    Map & _map;
};

#endif
