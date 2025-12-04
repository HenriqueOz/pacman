#include <cstdio>

#include "ecs/registry.hpp"
#include "game/input_manager.hpp"
#include "world.hpp"

int
main(int argc, char ** argv)
{
    InputManager inputManager = InputManager();
    ecs::Registry registry = ecs::Registry();

    World world = World(registry);

    return 0;
}
