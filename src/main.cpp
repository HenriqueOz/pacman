#include <unordered_map>

#include "SDL3/SDL_keycode.h"

#include "config/config.hpp"
#include "game/game.hpp"
#include "game/input.hpp"
#include "game/input_manager.hpp"
#include "game/map.hpp"
#include "game/world.hpp"
#include "game/collision_manager.hpp"

int
main(int argc, char ** argv)
{
    std::unordered_map<SDL_Keycode, Key> keyStates;
    CollisionGrid grid{};

    InputManager inputManager = InputManager(keyStates);
    Input input = Input(keyStates);
    CollisionManager collision = CollisionManager(grid);
    Map map = Map(config::assets::kMapCsv);

    World world = World(map);

    Game game = Game(world, inputManager, input, collision);

    game.run();

    return 0;
}
