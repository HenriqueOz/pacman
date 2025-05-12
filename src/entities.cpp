#include "entities.h"
#include "config.h"

// TODO change to grid tile system
// Make a hybrid collision system with bouding boxes
Entities::Entities()
{
    m_grid.resize(
      Config::verticalTiles,
      std::vector<std::vector<Entity *>>(Config::horizontalTiles, std::vector<Entity *>()));
}
