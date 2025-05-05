#include "map.h"
#include "collider.h"
#include "config.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

Map::Map(std::string filePath, Entities &entities)
  : m_entities(entities)
{
    this->loadMap(filePath);
}

void
Map::loadMap(std::string filePath)
{
    std::ifstream file;
    std::string line;

    file.open(filePath.c_str(), std::ios::in);

    if (!file.is_open()) {
        std::cerr << "Failed to open map file: " << filePath << std::endl;
        return;
    }

    unsigned row = 0;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string value;
        std::vector<unsigned> ids;

        while (std::getline(ss, value, ',')) {
            ids.push_back(std::stoi(value));
        }

        for (int i = 0; i < ids.size(); i++) {
            const unsigned x = (i % Config::horizontalTiles) * Config::tileWidth;
            const unsigned y = row * Config::tileHeight;
            const Vec2 pos = { static_cast<float>(x), static_cast<float>(y) };

            // m_entities[pos].push_back(std::make_unique<Collider>(pos));
        }
        row++;
    }

    file.close();
}

// void
// Map::printMapToFile() const
// {
//     std::ofstream output("map.txt");
//     if (!output.is_open()) {
//         std::cerr << "Failed to open map.txt" << std::endl;
//         return;
//     }

//     for (int j = 0; j < Config::verticalTiles; j++) {
//         for (int i = 0; i < Config::horizontalTiles; i++) {
//             const unsigned x = i * Config::tileWidth;
//             const unsigned y = j * Config::tileHeight;

//             const Vec2 pos = Vec2(static_cast<float>(x), static_cast<float>(y));
//             const auto it = map.find(pos);
//             const int value = (it != map.end()) ? it->second : 0;

//             if (value < 0) {
//                 output << "  ";
//             } else {
//                 output << value << " ";
//             }
//         }
//         output << "\n";
//     }

//     output.close();
// }
