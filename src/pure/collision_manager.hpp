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

    bool is_colliding_with_tag(const CollisionBox & box,
                               const CollisionTag tag) const;
    void update_box_on_map(const CollisionBox & box);

  private:
    MapGrid & _grid;

    Vec2<int> position_to_grid_cell(const Vec2<float> & position) const;
    bool is_cell_on_bounds(const Vec2<int> & cell) const;
    Vec2<float> get_box_center_position(const CollisionBox & box) const;
    inline std::vector<CollisionTag> & get_cell_tags(
      const Vec2<int> & cell) const
    {
        return _grid[cell.x][cell.y];
    }
};
;

#endif
