
#include "entities/gui_manager/gui_manager.h"
#include "game/controller/game_controller.h"
#include "game/entities/entities.h"
#include "game/input/input_manager.h"
#include <SDL3/SDL_error.h>
#include <config/config.h>
#include <cstdlib>
#include <game/game.h>
#include <game/map/map.h>
#include <iostream>
#include <memory>
#include <ostream>

int
main(int argc, char **argv)
{
    if (!TTF_Init()) {
        std::cerr << "ERROR::MAIN::FAILED_TO_INTIALIZE_TTF: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    auto inputManager = std::make_unique<InputManager>();
    auto entities = std::make_unique<Entities>();
    auto gameController = std::make_unique<GameController>(entities.get());

    Map::loadMap(Config::mapFilePath, entities.get(), gameController.get(), inputManager.get());

    entities->addEntity(std::make_unique<GuiManager>(gameController.get()));

    Game game(inputManager.get(), entities.get(), gameController.get());
    game.run();

    return 0;
}
