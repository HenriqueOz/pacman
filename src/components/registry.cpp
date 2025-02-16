#include "registry.hpp"

void
Registry::destroy_entity(Entity entity)
{
    sprites.erase(entity);
    transforms.erase(entity);
    velocities.erase(entity);
    inputs.erase(entity);
    colliders.erase(entity);
    pacman_tags.erase(entity);
    ghost_tags.erase(entity);
    food_tags.erase(entity);
    wall_tags.erase(entity);
}
