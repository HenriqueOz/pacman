#include "entity.h"
#include "game.h"
#include "ghost.h"
#include "input_manager.h"
#include "map.h"
#include "pacman.h"
#include <vector>

namespace Config {
const std::string assetsPath = "assets";
const std::string mapFilePath = assetsPath + "/map.csv";
const std::string windowName = "Pacman";

const unsigned windowWidth = TILE_WIDTH * VERTICAL_TILES * VERTICAL_SCALE;
const unsigned windowHeight = TILE_HEIGHT * HORIZONTAL_TILES * HORIZONTAL_SCALE;
const float aspectRatio = windowWidth / windowHeight;

const Uint16 FPS = 60;
const Uint16 frameDelay = 1000 / FPS;
}

void
initializeGame(Game *game, Window &window, Map &map);
std::vector<std::unique_ptr<Entity>>
createEntities(InputManager &inputManager);
void
gameLoop(Game *game, InputManager &inputManager, std::vector<std::unique_ptr<Entity>> &entities);

int
main(int argc, char **argv)
{
    InputManager inputManager = InputManager();
    Game *const game = Game::getInstance();
    Map map = Map(Config::mapFilePath);
    Window window = Window(Config::windowName.c_str(), Config::windowWidth, Config::windowHeight);
    std::vector<std::unique_ptr<Entity>> entities;

    initializeGame(game, window, map);
    entities = createEntities(inputManager);
    gameLoop(game, inputManager, entities);

    return 0;
}

void
initializeGame(Game *game, Window &window, Map &map)
{
    map.printMapToFile();
    game->init(&window);
}

void
gameLoop(Game *game, InputManager &inputManager, std::vector<std::unique_ptr<Entity>> &entities)
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

std::vector<std::unique_ptr<Entity>>
createEntities(InputManager &inputManager)
{
    std::vector<std::unique_ptr<Entity>> entities;

    Pacman *pacman = new Pacman(&inputManager);
    Ghost *ghost = new Ghost(&inputManager);

    entities.push_back(std::make_unique<Pacman>(&inputManager));
    entities.push_back(std::make_unique<Ghost>(&inputManager));

    return entities;
}
