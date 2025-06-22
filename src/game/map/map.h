#ifndef MAP_H_
#define MAP_H_

#include <components/input/input_manager.h>
#include <config/config.h>
#include <entities/entities.h>
#include <entities/entity.h>
#include <memory>
#include <string>
#include <unordered_map>
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
    void loadMap(std::string filePath);

    Entities &m_entities;
    InputManager &m_inputManager;

  public:
    Map(std::string, Entities &entities, InputManager &inputManager);
    ~Map(){};

    void printMapToFile() const {};
};

#endif