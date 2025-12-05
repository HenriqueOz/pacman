#ifndef REGISTRY_H_
#define REGISTRY_H_

#include <bitset>
#include <cstddef>
#include <cstdint>
#include <queue>
#include <typeindex>
#include <unordered_map>
#include <variant>

#include "components.hpp"

namespace ecs {

using Entity = std::uint64_t;

using Component = std::variant<Sprite, DirectionControl, Position, Velocity>;

class Registry
{
  private:
    Entity _lastEntityId = 0;
    std::uint64_t _livingEntitiesCount = 0;

    std::unordered_map<Entity, std::bitset<std::variant_size_v<Component>>> _entityComponents;
    std::unordered_map<Entity, std::unordered_map<std::type_index, Component>> _components;
    std::unordered_map<std::type_index, std::size_t> _componentsIndexes;

    std::queue<Entity> _freeEntities;

  public:
    Registry() { register_components_from_variant(Component{}); }

    ~Registry() = default;

    inline const Entity create_entity()
    {
        if (!_freeEntities.empty()) {
            Entity id = _freeEntities.front();
            _freeEntities.pop();
            return id;
        }
        ++_livingEntitiesCount;
        return ++_lastEntityId;
    }

    inline const void delete_entity(Entity id)
    {
        _freeEntities.push(id);
        --_livingEntitiesCount;
    }

    template<typename C>
    const bool has(Entity id) const
    {
        const auto it = _entityComponents.find(id);
        if (it == _entityComponents.end())
            return false;

        std::size_t idx = _componentsIndexes.at(std::type_index(typeid(C)));
        return it->second.test(idx);
    }

    template<typename C>
    inline void set(Entity id, Component && component)
    {
        std::type_index typeIdx(typeid(std::decay_t<C>));
        std::size_t componentIdx = _componentsIndexes.at(typeIdx);

        _components[id][typeIdx] = std::forward<C>(component);
        _entityComponents[id].set(componentIdx);
    }

  private:
    template<typename... C>
    inline void register_components_from_variant(std::variant<C...>)
    {
        std::size_t index = 0;
        ([&] { _componentsIndexes[std::type_index(typeid(C))] = index++; }(), ...);
    }
};

}

#endif