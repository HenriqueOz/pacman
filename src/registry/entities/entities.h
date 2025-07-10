#ifndef ENTITIES_H_
#define ENTITIES_H_

#include "entities/entity.h"
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

    inline std::unordered_map<Uint32, std::unique_ptr<Entity>> &getEntities() { return m_entities; }

    inline void updateEntityPositionInMap(Entity *entity, Vec2 const &current, Vec2 const &past)
    {
        Vec2 newPos = fixPositionToGrid(current);
        Vec2 oldPos = fixPositionToGrid(past);

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

    template<EntityType T>
    inline Entity *getEntityAt(int x, int y) const
    {
        const auto pos = fixPositionToGrid({ x, y });
        if (!isInBounds(pos)) {
            return nullptr;
        }

        const auto &entities = m_grid[pos.y][pos.x];

        for (const auto &entity : entities) {
            if (entity->getType() == T) {
                return entity;
            }
        }

        return nullptr;
    }

    template<EntityType T>
    inline bool hasEntityAt(int x, int y) const
    {
        return getEntityAt<T>(x, y) != nullptr;
    }

    template<EntityType T>
    inline bool deleteEntityAt(int x, int y)
    {
        const auto pos = fixPositionToGrid({ x, y });
        if (!isInBounds(pos)) {
            return false;
        }

        std::vector<Entity *> &entities = m_grid[pos.y][pos.x];

        for (auto it = entities.begin(); it != entities.end(); it++) {
            if ((*it)->getType() == T) {
                const auto entity = (*it);
                m_entities.at(entity->getId()).reset();
                m_entities.erase(entity->getId());
                entities.erase(it);

                return true;
            }
        }

        return false;
    }

  private:
    inline Vec2 fixPositionToGrid(Vec2 const &pos) const
    {
        Vec2 fixedPos = { 0, 0 };
        fixedPos.x = (pos.x / Config::tileWidth);
        fixedPos.y = (pos.y / Config::tileHeight);
        return fixedPos;
    }

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