#include <config/config.h>
#include <entities/entities.h>

Entities::Entities()
{
    m_grid.resize(
      Config::verticalTiles,
      std::vector<std::vector<Entity *>>(Config::horizontalTiles, std::vector<Entity *>()));
}
