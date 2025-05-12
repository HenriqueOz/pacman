#ifndef ENTITIES_H_
#define ENTITIES_H_

#include "config.h"
#include "entity.h"
#include <algorithm>
#include <memory>
#include <vector>

class Entities
{
  public:
    Entities();
    ~Entities(){};

    inline Entity *addEntity(std::unique_ptr<Entity> entity)
    {
        Entity *entityPtr = entity.get();
        m_entities.push_back(std::move(entity));

        std::sort(m_entities.begin(),
                  m_entities.end(),
                  [](const std::unique_ptr<Entity> &a, const std::unique_ptr<Entity> &b) {
                      return a->getType() == EntityType::PACMAN;
                  });

        return entityPtr;
    }

    inline std::vector<std::unique_ptr<Entity>> &getEntities() { return m_entities; }

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
    bool hasEntityAt(int x, int y) const
    {
        return getEntityAt<T>(x, y) != nullptr;
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

    std::vector<std::unique_ptr<Entity>> m_entities;
    std::vector<std::vector<std::vector<Entity *>>> m_grid;
};
#endif