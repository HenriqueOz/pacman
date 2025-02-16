#include "world.hpp"
#include "components/registry.hpp"

World::World(Registry & registry)
  : _registry(registry)
{
}

void
World::update(float delta_time, InputManager & input_manager)
{
}

void
World::render(SDL_Renderer * renderer)
{
}
