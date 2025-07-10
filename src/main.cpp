#include "registry/entities/entities.h"
#include "registry/registry.h"
#include <config/config.h>
#include <game/game.h>
#include <game/map/map.h>
#include <memory>

int
main(int argc, char **argv)
{
    const auto inputManager = Registry::registryInputManager(std::make_unique<InputManager>());
    const auto entities = Registry::registryEntitiesRegistry(std::make_unique<Entities>());

    Map::loadMap(Config::mapFilePath, entities);

    Game game = Game();
    game.run(inputManager, entities);

    return 0;
}