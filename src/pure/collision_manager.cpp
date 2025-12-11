#include "collision_manager.hpp"
#include "config/config.hpp"

CollisionManager::CollisionManager(MapGrid & grid)
  : _grid(grid)
{
}

void
CollisionManager::update_box_on_map(const CollisionBox & box)
{
    const Vec2<int> topLeftCell = position_to_grid_cell(box.get_position());
    const Vec2<int> bottomRightCell = position_to_grid_cell(
      { box.get_position().x + box.size.x, box.get_position().y + box.size.y });
}

Vec2<int>
CollisionManager::position_to_grid_cell(const Vec2<float> & position) const
{
    const int cellX = static_cast<int>(position.x) / config::tile::kTileWidth;
    const int cellY = static_cast<int>(position.y) / config::tile::kTileHeight;
    return { cellX, cellY };
}