#ifndef REGISTY_H
#define REGISTY_H

#include "components/collider.hpp"
#include "components/input.hpp"
#include "components/sprite.hpp"
#include "components/tags.hpp"
#include "components/tranform.hpp"
#include "components/velocity.hpp"
#include "entities/entity.hpp"
#include <unordered_map>

class Registry
{
  public:
    std::unordered_map<Entity, Sprite> sprites;
    std::unordered_map<Entity, Transform> transforms;
    std::unordered_map<Entity, Velocity> velocities;
    std::unordered_map<Entity, Input> inputs;
    std::unordered_map<Entity, Collider> colliders;

    std::unordered_map<Entity, PacmanTag> pacman_tags;
    std::unordered_map<Entity, GhostTag> ghost_tags;
    std::unordered_map<Entity, FoodTag> food_tags;
    std::unordered_map<Entity, WallTag> wall_tags;

    void destroy_entity(Entity entity);
};

#endif
