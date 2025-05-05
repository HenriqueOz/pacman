#ifndef MAP_H_
#define MAP_H_

#include "config.h"
#include "entity.h"
#include "vec.h"
#include <memory>
#include <string>
#include <unordered_map>

class Map
{
  private:
    void loadMap(std::string filePath);

  public:
    Map(std::string);
    ~Map(){};

    void printMapToFile() const {};
};

#endif