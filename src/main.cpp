#include <cstdio>
#include <unordered_map>

#include "SDL3/SDL_keycode.h"

#include "game/game.hpp"
#include "game/input.hpp"
#include "game/input_manager.hpp"
#include "world.hpp"

int
main(int argc, char ** argv)
{
    std::unordered_map<SDL_Keycode, Key> keyStates;

    InputManager inputManager = InputManager(keyStates);
    Input input = Input(keyStates);

    World world = World();

    Game game = Game(world, inputManager, input);

    game.run();

    return 0;
}
