#include <unordered_map>

#include "SDL3/SDL_keycode.h"

#include "game/game.hpp"
#include "game/input.hpp"
#include "game/input_manager.hpp"
#include "game/world.hpp"
#include "game/collision_manager.hpp"

int
main(int argc, char ** argv)
{
    std::unordered_map<SDL_Keycode, Key> keyStates;
    MapGrid grid{};

    InputManager inputManager = InputManager(keyStates);
    Input input = Input(keyStates);
    CollisionManager collision = CollisionManager(grid);

    World world = World();

    Game game = Game(world, inputManager, input, collision);

    game.run();

    return 0;
}
