
#include "game/controller/game_controller.h"
#include "game/entities/entities.h"
#include "game/input/input_manager.h"
#include <config/config.h>
#include <game/game.h>
#include <game/map/map.h>
#include <memory>

int
main(int argc, char **argv)
{
    auto inputManager = std::make_unique<InputManager>();
    auto entities = std::make_unique<Entities>();
    auto gameController = std::make_unique<GameController>(entities.get());

    Map::loadMap(Config::mapFilePath, entities.get(), gameController.get(), inputManager.get());

    Game game(inputManager.get(), entities.get(), gameController.get());
    game.run();

    return 0;
}