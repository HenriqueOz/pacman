#ifndef MAP_H_
#define MAP_H_

#include "registry/entities/entities.h"
#include <config/config.h>
#include <entities/entity.h>
#include <registry/input/input_manager.h>
#include <string>
#include <vec/vec.h>

enum MapId
{
    EMPTY = 0,
    WALL = 1,
    GHOST_DOOR = 2,
    PACMAN_SPAWN = 3,
};

class Map
{
  private:
    Map();

  public:
    ~Map() {};

    static void loadMap(std::string filePath, Entities *entitiesRegistry);
    static void printMapToFile() {};
};

#endif