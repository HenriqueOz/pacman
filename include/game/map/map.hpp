#ifndef MAP_HPP_
#define MAP_HPP_

#include "game/controller/game_controller.hpp"
#include "game/entities/entities.hpp"
#include <config/config.hpp>
#include <entities/entity.hpp>
#include <game/input/input_manager.hpp>
#include <string>
#include <vec/vec.hpp>

enum class MapId : int
{
    EMPTY = -1,
    FOOD = 0,
    WALL = 1,
    GHOST_DOOR = 2,
    PACMAN_SPAWN = 3,
    BLINKY = 4,
    PINKY = 5,
    INKY = 6,
    CLYDE = 7,
    SUPER_FOOD = 8,
};

class Map
{
  private:
    Map();
    static void addEntity(int id,
                          Vec2 const & pos,
                          Entities * entitiesRegistry,
                          GameController * gameController,
                          InputManager * inputManager);

  public:
    ~Map() {};

    static void loadMap(std::string filePath,
                        Entities * entitiesRegistry,
                        GameController * gameController,
                        InputManager * inputManager);
};

#endif
