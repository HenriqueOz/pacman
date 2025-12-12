#ifndef COLLISION_MANAGER_H_
#define COLLISION_MANAGER_H_

#include <vector>
#include <array>

#include "config/config.hpp"
#include "pure/collision_box.hpp"

using MapGrid = std::array<
  std::array<std::vector<CollisionTag>, config::tile::kHorizontalTiles>,
  config::tile::kVerticalTiles>;

class CollisionManager
{
  public:
    CollisionManager(MapGrid & grid);
    ~CollisionManager() = default;

    void update_box_on_map(const CollisionBox & box);

  private:
    MapGrid & _grid;

    Vec2<int> position_to_grid_cell(const Vec2<float> & position) const;
};
;

#endif
