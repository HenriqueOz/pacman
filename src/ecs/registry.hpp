#ifndef REGISTRY_H_
#define REGISTRY_H_

#include <bitset>
#include <cstddef>
#include <cstdint>
#include <queue>
#include <tuple>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

#include "components.hpp"

namespace ecs {

using Entity = std::uint64_t;

using Component = std::variant<Sprite, DirectionControl, Position, Velocity>;

class Registry
{
  public:
    Registry() { register_components_from_variant(Component{}); }

    ~Registry() = default;

    inline const std::uint64_t entities_count() { return _livingEntitiesCount; }

    inline const Entity create_entity()
    {
        ++_livingEntitiesCount;
        if (!_freeEntities.empty()) {
            Entity id = _freeEntities.front();
            _freeEntities.pop();
            return id;
        }
        return ++_lastEntityId;
    }

    inline const void delete_entity(Entity id)
    {
        _freeEntities.push(id);
        --_livingEntitiesCount;

        _entities.erase(id);
    }

    template<typename C>
    const bool has(Entity id) const
    {
        const auto it = _entities.find(id);
        if (it == _entities.end())
            return false;

        std::size_t idx = get_component_index<C>();
        const ComponentBitset & bitset = std::get<1>(it->second);

        return bitset.test(idx);
    }

    template<typename C>
    inline void set(Entity id, C && component)
    {
        std::type_index typeIndex(typeid(std::decay_t<C>));
        std::size_t componentIndex = _componentsIndexes.at(typeIndex);

        std::tuple<std::unordered_map<std::size_t, Component>,
                   ComponentBitset> & data = _entities[id];

        std::unordered_map<std::size_t, Component> & components =
          std::get<0>(data);
        components[componentIndex] = component;

        ComponentBitset & bitset = std::get<1>(data);
        bitset.set(componentIndex);
    }

    template<typename C>
    C * get(Entity id)
    {
        const auto & it = _entities.find(id);
        if (it == _entities.end())
            return nullptr;

        std::size_t idx = get_component_index<C>();
        const ComponentBitset & bitset = std::get<1>(it->second);

        if (!bitset.test(idx))
            return nullptr;

        std::unordered_map<std::size_t, Component> & components =
          std::get<0>(it->second);

        const auto & componentIt = components.find(idx);
        if (componentIt == components.end())
            return nullptr;

        return std::get_if<C>(&componentIt->second);
    }

    template<typename C>
    const C * get(Entity id) const
    {
        auto it = _entities.find(id);
        if (it == _entities.end())
            return nullptr;

        std::size_t componentIndex = get_component_index<C>();
        const ComponentBitset & bitset = std::get<1>(it->second);

        if (!bitset.test(componentIndex))
            return nullptr;

        const std::unordered_map<std::size_t, Component> & entityComponents =
          std::get<0>(it->second);

        const auto & componentIt = entityComponents.find(componentIndex);
        if (componentIt == entityComponents.end())
            return nullptr;

        return std::get_if<C>(&componentIt->second);
    }

    template<typename... C>
    std::vector<Entity> view()
    {
        std::vector<Entity> queryEntitites;

        ComponentBitset mask;
        (
          [&] {
              std::size_t idx = get_component_index<C>();
              mask.set(idx);
          }(),
          ...);

        for (const auto & [entityId, entityData] : _entities) {
            const ComponentBitset & entityBitset = std::get<1>(entityData);

            if ((mask & entityBitset) == mask) {
                queryEntitites.push_back(entityId);
            }
        }

        return queryEntitites;
    }

  private:
    using ComponentBitset = std::bitset<std::variant_size_v<Component>>;

    Entity _lastEntityId = 0;
    std::uint64_t _livingEntitiesCount = 0;

    std::unordered_map<
      Entity,
      std::tuple<std::unordered_map<std::size_t, Component>, ComponentBitset>>
      _entities;
    std::unordered_map<std::type_index, std::size_t> _componentsIndexes;

    std::queue<Entity> _freeEntities;

    template<typename... C>
    inline void register_components_from_variant(std::variant<C...>)
    {
        std::size_t index = 0;
        ([&] { _componentsIndexes[std::type_index(typeid(C))] = index++; }(),
         ...);
    }

    template<typename C>
    const std::size_t get_component_index() const
    {
        return _componentsIndexes.at(std::type_index(typeid(C)));
    }
};

} // namespace ecs

#endif