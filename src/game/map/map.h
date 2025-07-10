#ifndef MAP_H_
#define MAP_H_

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
};

class Map
{
  private:
    Map();
    static void addEntity(int id, Vec2 const &pos, Entities *entitiesRegistry);

  public:
    ~Map() {};

    static void loadMap(std::string filePath, Entities *entitiesRegistry);
    static void printMapToFile() {};
};

#endif