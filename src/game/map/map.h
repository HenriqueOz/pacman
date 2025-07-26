#ifndef MAP_H_
#define MAP_H_

#include "registry/controller/game_controller.h"
#include "registry/entities/entities.h"
#include <config/config.h>
#include <entities/entity.h>
#include <registry/input/input_manager.h>
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
};

class Map
{
  private:
    Map();
    static void addEntity(int id,
                          Vec2 const &pos,
                          Entities *entitiesRegistry,
                          GameController *gameController);

  public:
    ~Map() {};

    static void loadMap(std::string filePath,
                        Entities *entitiesRegistry,
                        GameController *gameController);
    static void printMapToFile() {};
};

#endif