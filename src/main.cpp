#include "main.h"
#include "game.h"

int
main(int argc, char **argv)
{
    pm::Game *const game = pm::Game::getInstance();
    game->init();

    while (game->isRunning()) {
        game->update();
        game->render();
    }

    return 0;
}