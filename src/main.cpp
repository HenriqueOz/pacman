#include "registry/entities/entities.h"
#include "registry/registry.h"
#include <config/config.h>
#include <game/game.h>
#include <game/map/map.h>
#include <game/window/window.h>
#include <memory>

int
main(int argc, char **argv)
{
    auto inputManager = Registry::registryInputManager(std::make_unique<InputManager>());
    auto entities = Registry::registryEntitiesRegistry(std::make_unique<Entities>());

    Map::loadMap(Config::mapFilePath, entities);

    Window window = Window(Config::windowName.c_str(), Config::windowWidth, Config::windowHeight);

    Game game = Game();
    game.run(window, inputManager, entities);

    return 0;
}