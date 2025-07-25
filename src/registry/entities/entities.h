#ifndef ENTITIES_H_
#define ENTITIES_H_

#include "entities/entity.h"
#include "entities/utils/utils.h"
#include "vec/vec.h"
#include <SDL3/SDL_stdinc.h>
#include <algorithm>
#include <config/config.h>
#include <memory>
#include <unordered_map>
#include <vector>

class Entities
{
  public:
    Entities();
    ~Entities() {};

    inline Entity *addEntity(std::unique_ptr<Entity> entity)
    {
        Entity *entityPtr = entity.get();
        const Uint32 id = m_currentId++;

        entity->setId(id);
        m_entities.insert({ id, std::move(entity) });

        return entityPtr;
    }

    inline std::vector<Entity *> getEntitiesSortedByDepth() const
    {
        std::vector<Entity *> sortedEntities;
        sortedEntities.reserve(m_entities.size());

        for (const auto &pair : m_entities) {
            if (pair.second != nullptr) {
                sortedEntities.push_back(pair.second.get());
            }
        }

        std::sort(sortedEntities.begin(), sortedEntities.end(), [](Entity *a, Entity *b) {
            return static_cast<int>(a->getType()) > static_cast<int>(b->getType());
        });

        return sortedEntities;
    }

    inline std::unordered_map<Uint32, std::unique_ptr<Entity>> &getEntities() { return m_entities; }

    inline void updateEntityPositionInMap(Entity *entity, Vec2 const &current, Vec2 const &past)
    {
        Vec2 newPos = Utils::fixPositionToGrid(current);
        Vec2 oldPos = Utils::fixPositionToGrid(past);

        if (isInBounds(oldPos)) {
            auto &entities = m_grid[oldPos.y][oldPos.x];
            auto it = std::remove(entities.begin(), entities.end(), entity);
            if (it != entities.end()) {
                entities.erase(it, entities.end());
            }
        }

        if (isInBounds(newPos)) {
            auto &entities = m_grid[newPos.y][newPos.x];
            auto it = std::find(entities.begin(), entities.end(), entity);
            if (it == entities.end()) {
                entities.push_back(entity);
            }
        }
    }

    inline Entity *getEntityAt(int x, int y, EntityType type) const
    {
        const auto pos = Utils::fixPositionToGrid({ x, y });
        if (!isInBounds(pos)) {
            return nullptr;
        }

        const auto &entities = m_grid[pos.y][pos.x];

        for (const auto &entity : entities) {
            if (entity->getType() == type) {
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
        const auto pos = Utils::fixPositionToGrid({ x, y });
        if (!isInBounds(pos)) {
            return false;
        }

        std::vector<Entity *> &entities = m_grid[pos.y][pos.x];

        for (auto it = entities.begin(); it != entities.end(); it++) {
            const auto entity = (*it);
            if (entity->getType() == type) {
                const Uint32 id = entity->getId();
                m_entities.at(id).reset();
                m_entities.erase(id);
                entities.erase(it);

                return true;
            }
        }

        return false;
    }

    inline Entity *getEntityById(Uint32 id)
    {
        const auto it = m_entities.find(id);
        if (it == m_entities.end()) {
            return nullptr;
        }

        return it->second.get();
    }

  private:
    inline bool isInBounds(Vec2 const &pos) const
    {
        return pos.x >= 0 && pos.x < Config::horizontalTiles && pos.y >= 0 &&
               pos.y < Config::verticalTiles;
    }

    Uint32 m_currentId = 1000;

    std::unordered_map<Uint32, std::unique_ptr<Entity>> m_entities;
    std::vector<std::vector<std::vector<Entity *>>> m_grid;
};
#endif