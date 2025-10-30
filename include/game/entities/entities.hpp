#ifndef ENTITIES_HPP_
#define ENTITIES_HPP_

#include "entities/entity.hpp"
#include "vec/vec.hpp"
#include <SDL3/SDL_stdinc.h>
#include <algorithm>
#include <config/config.hpp>
#include <memory>
#include <unordered_map>
#include <vector>

class Entities
{
  public:
    Entities() {};
    ~Entities() {};

    inline Entity * addEntity(std::unique_ptr<Entity> entity)
    {
        Entity * entityPtr = entity.get();
        const Uint32 id = m_currentId++;

        entity->setId(id);
        m_entities.insert({ id, std::move(entity) });

        return entityPtr;
    }

    inline std::vector<Entity *> getEntitiesSortedByDepth() const
    {
        std::vector<Entity *> sortedEntities;
        sortedEntities.reserve(m_entities.size());

        for (const auto & pair : m_entities) {
            if (pair.second != nullptr) {
                sortedEntities.push_back(pair.second.get());
            }
        }

        std::sort(sortedEntities.begin(), sortedEntities.end(), [](Entity * a, Entity * b) {
            return static_cast<int>(a->getType()) > static_cast<int>(b->getType());
        });

        return sortedEntities;
    }

    inline std::unordered_map<Uint32, std::unique_ptr<Entity>> & getEntities()
    {
        return m_entities;
    }

    inline Entity * getEntityAt(int x, int y, EntityType type) const
    {
        for (const auto & pair : m_entities) {
            Entity * entity = pair.second.get();
            if (entity && entity->getType() == type && isPositionInEntityBounds(x, y, entity)) {
                return entity;
            }
        }
        return nullptr;
    }

    inline bool hasEntityAt(int x, int y, EntityType type) const
    {
        return getEntityAt(x, y, type) != nullptr;
    }

    inline bool deleteEntityAt(int x, int y, EntityType type)
    {
        for (auto it = m_entities.begin(); it != m_entities.end(); ++it) {
            Entity * entity = it->second.get();
            if (entity && entity->getType() == type && isPositionInEntityBounds(x, y, entity)) {
                m_entities.erase(it);
                return true;
            }
        }
        return false;
    }

    inline Entity * getEntityById(Uint32 id)
    {
        const auto it = m_entities.find(id);
        if (it == m_entities.end()) {
            return nullptr;
        }

        return it->second.get();
    }

  private:
    inline bool isPositionInEntityBounds(int x, int y, Entity * entity) const
    {
        Vec2 pos = entity->getPosition();
        Vec2 size = entity->getSize();

        return x >= pos.x && x < pos.x + size.x && y >= pos.y && y < pos.y + size.y;
    }

    Uint32 m_currentId = 1000;
    std::unordered_map<Uint32, std::unique_ptr<Entity>> m_entities;
};
#endif
