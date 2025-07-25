#include "map.h"
#include "config/config.h"
#include "entities/food/food.h"
#include "entities/ghost/ghost.h"
#include "registry/controller/game_controller.h"
#include "registry/entities/entities.h"
#include "vec/vec.h"
#include <cctype>
#include <entities/collider/collider.h>
#include <entities/pacman/pacman.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

void
Map::loadMap(std::string filePath, Entities *entitiesRegistry, GameController *gameController)
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
        char value;
        std::vector<int> ids;

        for (int i = 0; i < line.length(); i++) {
            value = line[i];
            if (std::isdigit(value)) {
                ids.push_back(value - '0');
            } else if (value == '#') {
                ids.push_back(static_cast<int>(MapId::EMPTY));
            }
        }

        for (int i = 0; i < ids.size(); i++) {
            const int x = (i % Config::horizontalTiles) * Config::tileWidth;
            const int y = row * Config::tileHeight;
            const Vec2 pos = { x, y };

            addEntity(ids[i], pos, entitiesRegistry, gameController);
        }
        row++;
    }

    file.close();
}

void
Map::addEntity(int id, Vec2 const &pos, Entities *entitiesRegistry, GameController *gameController)
{
    const Vec2 wallSize = {
        Config::tileWidth,
        Config::tileHeight,
    };

    switch (id) {
        case static_cast<int>(MapId::FOOD):
            entitiesRegistry->addEntity(std::make_unique<Food>(pos));
            break;
        case static_cast<int>(MapId::WALL):
            entitiesRegistry->addEntity(std::make_unique<Collider>(pos, wallSize, false));
            break;
        case static_cast<int>(MapId::GHOST_DOOR): {
            Entity *ghostDoor =
              entitiesRegistry->addEntity(std::make_unique<Collider>(pos, wallSize, true));
            gameController->registerGhostDoorId(ghostDoor->getId());
        } break;
        case static_cast<int>(MapId::PACMAN_SPAWN): {
            Entity *pacman = entitiesRegistry->addEntity(std::make_unique<Pacman>(pos));
            gameController->registerPacmanId(pacman->getId());
        } break;
        case static_cast<int>(MapId::GHOST_RED):
            entitiesRegistry->addEntity(std::make_unique<Ghost>(pos));
            break;
    }
}
