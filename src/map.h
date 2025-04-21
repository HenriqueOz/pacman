#ifndef MAP_H_
#define MAP_H_

#include "vec.h"
#include <string>
#include <unordered_map>

const unsigned HORIZONTAL_TILES = 28;
const unsigned VERTICAL_TILES = 31;
const unsigned TILE_WIDTH = 16;
const unsigned TILE_HEIGHT = 16;
const unsigned HORIZONTAL_SCALE = 2;
const unsigned VERTICAL_SCALE = 2;

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