
#include "registry/controller/game_controller.h"
#include "registry/entities/entities.h"
#include "registry/input/input_manager.h"
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
    const auto gameController =
      Registry::registryGameController(std::make_unique<GameController>());

    Map::loadMap(Config::mapFilePath, entities, gameController);

    Game game = Game();
    game.run(inputManager, entities);

    return 0;
}