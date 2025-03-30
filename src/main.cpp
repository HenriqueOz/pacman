#include "entity.h"
#include "game.h"
#include "ghost.h"
#include "input_manager.h"
#include "pacman.h"
#include <vector>

int
main(int argc, char **argv)
{
    Game *const game = Game::getInstance();
    game->init();

    InputManager inputManager = InputManager();

    std::vector<Entity *> entities;

    Pacman pacman = Pacman(&inputManager);
    Ghost ghost = Ghost(&inputManager);
    entities.push_back(&pacman);
    entities.push_back(&ghost);

    while (game->isRunning()) {
        game->handleInput(&inputManager);
        game->update(entities);
        game->render(entities);
    }

    return 0;
}