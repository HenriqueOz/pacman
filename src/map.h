#ifndef MAP_H_
#define MAP_H_

#include "config.h"
#include "vec.h"
#include <string>
#include <unordered_map>

class Map
{
  public:
    Map(std::string);
    ~Map(){};

    void printMapToFile() const;

  private:
    void loadMap(std::string filePath);

    // Block position as key and block ID as value
    std::unordered_map<Vec2, int> map;
};

#endif