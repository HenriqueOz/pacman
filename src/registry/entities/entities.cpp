#include "entities.h"
#include <config/config.h>

Entities::Entities()
{
    m_grid.resize(
      Config::verticalTiles,
      std::vector<std::vector<Entity *>>(Config::horizontalTiles, std::vector<Entity *>()));
}
