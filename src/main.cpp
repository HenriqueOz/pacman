#include <components/input/input_manager.h>
#include <config/config.h>
#include <entities/entities.h>
#include <game/game.h>
#include <game/map/map.h>
#include <game/window/window.h>
#include <vector>

void
initializeGame(Game *game, Window &window);

void
createEntities(InputManager &inputManager, Entities &entities);

void
gameLoop(Game *game, InputManager &inputManager, Entities &entities);

int
main(int argc, char **argv)
{
    InputManager inputManager = InputManager();
    Entities entities = Entities();
    Map map = Map(Config::mapFilePath, entities, inputManager);
    Game *const game = Game::getInstance();
    Window window = Window(Config::windowName.c_str(), Config::windowWidth, Config::windowHeight);

    initializeGame(game, window);
    createEntities(inputManager, entities);
    gameLoop(game, inputManager, entities);

    return 0;
}

void
initializeGame(Game *game, Window &window)
{
    game->init(window);
}

void
gameLoop(Game *game, InputManager &inputManager, Entities &entities)
{
    Uint64 frameStart;
    Uint64 frameDuration;

    while (game->isRunning()) {
        frameStart = SDL_GetTicks();

        game->handleInput(&inputManager);
        game->update(entities);
        game->render(entities);

        frameDuration = SDL_GetTicks() - frameStart;
        if (Config::frameDelay > frameDuration) {
            SDL_Delay(Config::frameDelay - frameDuration);
        }
    }

    game->clean();
}

void
createEntities(InputManager &inputManager, Entities &entities)
{
}
