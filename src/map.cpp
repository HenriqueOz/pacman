#include "map.h"
#include "collider.h"
#include "config.h"
#include "pacman.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

enum MapId
{
    EMPTY = 0,
    WALL = 1,
    PACMAN_SPAWN = 3,
};

Map::Map(std::string filePath, Entities &entities, InputManager &inputManager)
  : m_entities(entities)
  , m_inputManager(inputManager)
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
                m_entities.addEntity(std::make_unique<Collider>(pos, size));
            } else if (ids[i] == MapId::PACMAN_SPAWN) {
                m_entities.addEntity(std::make_unique<Pacman>(pos, &m_inputManager, &m_entities));
            }
        }
        row++;
    }

    file.close();
}
