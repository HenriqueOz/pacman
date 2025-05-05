#include "entities.h"
#include "config.h"

Entities::Entities()
{
    m_entitiesMap.resize(Config::horizontalTiles,
                         std::vector<Entity *>(Config::verticalTiles, nullptr));
}
