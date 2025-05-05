#ifndef ENTITIES_H_
#define ENTITIES_H_

#include "entity.h"
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
        return entityPtr;
    }

    inline std::vector<std::unique_ptr<Entity>> &getEntities() { return m_entities; }

    

  private:
    std::vector<std::unique_ptr<Entity>> m_entities;
    std::vector<std::vector<Entity *>> m_entitiesMap;
};
#endif