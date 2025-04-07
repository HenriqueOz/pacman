#include "entity.h"
#include "game.h"
#include "ghost.h"
#include "input_manager.h"
#include "pacman.h"
#include <vector>

int
main(int argc, char **argv)
{
    Window window = Window("Pacman", 400, 400);

    Game *const game = Game::getInstance();
    game->init(&window);

    InputManager inputManager = InputManager();

    std::vector<Entity *> entities;

    Pacman pacman = Pacman(&inputManager);
    Ghost ghost = Ghost(&inputManager);
    entities.push_back(&pacman);
    entities.push_back(&ghost);

    const Uint16 FPS = 60;
    const Uint16 frameDelay = 1000 / FPS;

    Uint64 frameStart;
    Uint64 frameDuration;

    while (game->isRunning()) {
        frameStart = SDL_GetTicks();

        game->handleInput(&inputManager);
        game->update(entities);
        game->render(entities);

        frameDuration = SDL_GetTicks() - frameStart;

        if (frameDelay > frameDuration) {
            SDL_Delay(frameDelay - frameDuration);
        }
    }

    return 0;
}