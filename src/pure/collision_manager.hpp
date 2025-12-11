#ifndef COLLISION_MANAGER_H_
#define COLLISION_MANAGER_H_

#include <unordered_map>
#include <vector>
#include <array>

#include "pure/collision_box.hpp"
#include "pure/utils.hpp"
#include "config/config.hpp"

using GridCell = std::vector<const CollisionBox *>;

using MapGrid = std::array<std::array<GridCell, config::tile::kHorizontalTiles>,
                           config::tile::kVerticalTiles>;

class CollisionManager
{
  public:
    CollisionManager(MapGrid & grid);
    ~CollisionManager() = default;

    void register_box(const CollisionBox * box);
    void unregister_box(const CollisionBox * box);

    void update_box_position(const CollisionBox * box,
                             const Vec2<float> & oldPos,
                             const Vec2<float> & newPos);

    bool check_collision_at(const Vec2<float> & position,
                            const Vec2<int> & size,
                            CollisionTag tag) const;

    std::vector<const CollisionBox *> get_collisions_at(
      const Vec2<float> & position,
      const Vec2<int> & size) const;

  private:
    MapGrid & _grid;
    std::unordered_map<const CollisionBox *, std::vector<Vec2<int>>> _boxCells;

    Vec2<int> position_to_grid_cell(const Vec2<float> & position) const;
    bool is_cell_on_bounds(const Vec2<int> & cell) const;
    std::vector<Vec2<int>> get_cells_within(const Vec2<float> & position,
                                            const Vec2<int> & size) const;
    bool aabb_check(const Vec2<float> & p1,
                    const Vec2<int> & s1,
                    const Vec2<float> & p2,
                    const Vec2<int> & s2) const;
    inline GridCell & get_cell(const Vec2<int> & cell) const
    {
        return _grid[cell.x][cell.y];
    }
};

#endif
