#ifndef COLLISION_MANAGER_H_
#define COLLISION_MANAGER_H_

#include <unordered_map>
#include <vector>
#include <array>

#include "game/collision_box.hpp"
#include "game/utils.hpp"
#include "config/config.hpp"

using GridCell = std::vector<const CollisionBox *>;

using CollisionGrid = std::array<std::array<GridCell, config::tile::kVerticalTiles>, config::tile::kHorizontalTiles>;

class CollisionManager
{
  public:
    CollisionManager(CollisionGrid & grid);
    ~CollisionManager() = default;

    void register_box(const CollisionBox * box);
    void unregister_box(const CollisionBox * box);

    void update_box_position(CollisionBox * box, const Vec2<float> & newPos);

    bool check_collision_at(const Vec2<float> & position, const Vec2<int> & size, const CollisionTagBitMask mask) const;

    std::vector<const CollisionBox *> get_collisions_at(const Vec2<float> & position, const Vec2<int> & size) const;

  private:
    CollisionGrid & _grid;
    std::unordered_map<const CollisionBox *, std::vector<Vec2<int>>> _boxCells;

    Vec2<int> position_to_grid_cell(const Vec2<float> & position) const;
    bool is_cell_on_bounds(const Vec2<int> & cell) const;
    std::vector<Vec2<int>> get_cells_within(const Vec2<float> & position, const Vec2<int> & size) const;
    bool aabb_check(const Vec2<float> & p1, const Vec2<int> & s1, const Vec2<float> & p2, const Vec2<int> & s2) const;
    inline GridCell & get_cell(const Vec2<int> & cell) const { return _grid[cell.x][cell.y]; }
};

#endif
