#include "collision_manager.hpp"
#include "config/config.hpp"

CollisionManager::CollisionManager(MapGrid & grid)
  : _grid(grid)
{
}

void
CollisionManager::update_box_on_map(const CollisionBox & box)
{
    const Vec2<int> pastCenterCellPosition = this->position_to_grid_cell(
      { box.get_old_position().x + (box.size.x / 2.f),
        box.get_old_position().y + (box.size.y / 2.f) });
    const Vec2<int> currentCenterCellPosition = this->position_to_grid_cell(
      { box.get_position().x + (box.size.x / 2.f),
        box.get_position().y + (box.size.y / 2.f) });

    if (pastCenterCellPosition.x != currentCenterCellPosition.x ||
        pastCenterCellPosition.y != currentCenterCellPosition.y) {
        std::erase(_grid[pastCenterCellPosition.x][pastCenterCellPosition.y],
                   box.get_tag());

        _grid[currentCenterCellPosition.x][currentCenterCellPosition.y]
          .push_back(box.get_tag());
    }
}

Vec2<int>
CollisionManager::position_to_grid_cell(const Vec2<float> & position) const
{
    const int cellX = static_cast<int>(position.x) / config::tile::kTileWidth;
    const int cellY = static_cast<int>(position.y) / config::tile::kTileHeight;
    return { cellX, cellY };
}
