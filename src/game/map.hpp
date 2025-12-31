#ifndef MAP_H_
#define MAP_H_

#include <cstdint>
#include <filesystem>

enum MapTags : std::uint8_t
{
    kEmpty = 0,
    kWall = 1,
    kPellet = 2,
    kPacmanSpawn = 3,
    kTotalItems
};

using MapMatrix = std::vector<std::vector<MapTags>>;

class Map
{
  public:
    Map(const std::filesystem::path & filePath);

    const MapMatrix & get_map_matrix() const { return _map; }

  private:
    MapMatrix _map;

    void parse_map_and_store(const std::filesystem::path & filePath);
    MapTags map_tag_from_char(char value) const;
};

#endif