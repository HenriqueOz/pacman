#ifndef MAP_H_
#define MAP_H_

#include "game/controller/game_controller.h"
#include "game/entities/entities.h"
#include <config/config.h>
#include <entities/entity.h>
#include <game/input/input_manager.h>
#include <string>
#include <vec/vec.h>

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
};

class Map
{
  private:
    Map();
    static void addEntity(int id,
                          Vec2 const &pos,
                          Entities *entitiesRegistry,
                          GameController *gameController,
                          InputManager *inputManager);

  public:
    ~Map() {};

    static void loadMap(std::string filePath,
                        Entities *entitiesRegistry,
                        GameController *gameController,
                        InputManager *inputManager);
};

#endif