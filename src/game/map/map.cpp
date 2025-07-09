#include "map.h"
#include "registry/entities/entities.h"
#include <entities/collider/collider.h>
#include <entities/pacman/pacman.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void
Map::loadMap(std::string filePath, Entities *entitiesRegistry)
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
        std::vector<int> ids;

        while (std::getline(ss, value, ',')) {
            ids.push_back(std::stoi(value));
        }

        for (int i = 0; i < ids.size(); i++) {
            const int x = (i % Config::horizontalTiles) * Config::tileWidth;
            const int y = row * Config::tileHeight;
            const Vec2 pos = { x, y };
            const Vec2 size = { Config::tileWidth, Config::tileHeight };

            if (ids[i] == MapId::WALL) {
                entitiesRegistry->addEntity(std::make_unique<Collider>(pos, size, false));
            } else if (ids[i] == MapId::PACMAN_SPAWN) {
                entitiesRegistry->addEntity(std::make_unique<Pacman>(pos));
            } else if (ids[i] == MapId::GHOST_DOOR) {
                entitiesRegistry->addEntity(std::make_unique<Collider>(pos, size, true));
            }
        }
        row++;
    }

    file.close();
}
