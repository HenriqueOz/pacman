#ifndef REGISTRY_H_
#define REGISTRY_H_

#include <array>
#include <bitset>
#include <cstdint>
#include <queue>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <variant>
#include <vector>

#include "components.hpp"

namespace ecs {

using Entity = std::uint64_t;

using Component = std::variant<Sprite, DirectionControl, Position, Velocity>;

class Registry
{
  public:
    Registry() { _components.reserve(_componentTypes.size()); }

    ~Registry() = default;

    inline const Entity create_entity()
    {
        if (!_freeEntities.empty()) {
            Entity id = _freeEntities.front();
            _freeEntities.pop();
            return id;
        }
        return ++_lastEntity;
    }

    template<typename C>
    const bool has(Entity id) const
    {
        return _entityComponents.at(id).contains(std::type_index(typeid(C)));
    }

    inline void set(Entity id, std::vector<Component &> & components)
    {
        _entityComponents.insert({ id, std::bitset<std::variant_size_v<Component>>() });
    }

  private:
    Entity _lastEntity = 0;

    std::unordered_map<Entity, std::bitset<std::variant_size_v<Component>>> _entityComponents;
    std::unordered_map<std::type_index, std::pair<Component, Entity>> _components;

    std::array<std::type_info, std::variant_size_v<Component>> _componentTypes;

    std::queue<Entity> _freeEntities;
};

}

#endif