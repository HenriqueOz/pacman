#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "game/map.hpp"
#include "config/config.hpp"

Map::Map(const std::filesystem::path & filePath)
{
    _map = std::vector<std::vector<MapTags>>(config::tile::kVerticalTiles,
                                             std::vector<MapTags>(config::tile::kHorizontalTiles));

    parse_map_and_store(filePath);
}

void
Map::parse_map_and_store(const std::filesystem::path & filePath)
{
    std::fstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "ERROR::MAP::FAILED_TO_OPEN_MAP_FILE: " << filePath.string() << "\n";
        return;
    }

    int row = 0;
    int col = 0;
    std::string line;

    while (std::getline(file, line)) {
        for (const char c : line) {
            if (c == ' ')
                continue;

            const MapTags tag = map_tag_from_char(c);
            _map[row][col] = tag;

            if (col < _map[0].capacity() - 1) {
                col++;
            }
        }
        col = 0;
        if (row < _map.capacity() - 1) {
            row++;
        }
    }

    file.close();
}

MapTags
Map::map_tag_from_char(char value) const
{
    const int intValue = std::atoi(&value);
    if (intValue < 0 || intValue >= static_cast<int>(MapTags::kTotalItems)) {
        return MapTags::kEmpty;
    }

    return static_cast<MapTags>(intValue);
}