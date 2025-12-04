#include "world.hpp"
#include "ecs/components.hpp"
#include "ecs/registry.hpp"

World::World(ecs::Registry & registry)
  : _registry(registry)
{
    initialize();
}

void
World::initialize()
{
    ecs::Entity pacman = _registry.create_entity();
    _registry.set(pacman, ecs::Sprite{});
    _registry.set(pacman, ecs::DirectionControl{});
}

void
World::update(float deltaTime, InputManager & inputManager)
{
}

void
World::render(SDL_Renderer * renderer)
{
}
