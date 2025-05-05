#ifndef MAP_H_
#define MAP_H_

#include "config.h"
#include "entities.h"
#include "entity.h"
#include "vec.h"
#include <memory>
#include <string>
#include <unordered_map>

class Map
{
  private:
    void loadMap(std::string filePath);

    Entities &m_entities;

  public:
    Map(std::string, Entities &entities);
    ~Map(){};

    void printMapToFile() const {};
};

#endif