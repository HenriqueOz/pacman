#include <algorithm>
#include <vector>

#include "collision_manager.hpp"
#include "config/config.hpp"

CollisionManager::CollisionManager(MapGrid & grid)
  : _grid(grid)
{
}

bool
CollisionManager::is_colliding_with_tag(const CollisionBox & box,
                                        const CollisionTag tag) const
{
    const Vec2<int> centerCellPosition =
      this->position_to_grid_cell(this->get_box_center_position(box));

    if (!this->is_cell_on_bounds(centerCellPosition)) {
        return false;
    }

    const std::vector<CollisionTag> & cellTags =
      this->get_cell_tags(centerCellPosition);
    return (std::find(cellTags.begin(), cellTags.end(), tag) != cellTags.end());
}

void
CollisionManager::update_box_on_map(const CollisionBox & box)
{
    const Vec2<int> pastCenterCellPosition =
      this->position_to_grid_cell(this->get_box_center_position(box));
    const Vec2<int> currentCenterCellPosition =
      this->position_to_grid_cell(this->get_box_center_position(box));

    if (pastCenterCellPosition.is_equal(currentCenterCellPosition)) {
        return;
    }

    if (this->is_cell_on_bounds(pastCenterCellPosition)) {
        std::erase(this->get_cell_tags(pastCenterCellPosition), box.get_tag());
    }

    if (this->is_cell_on_bounds(currentCenterCellPosition)) {
        this->get_cell_tags(currentCenterCellPosition).push_back(box.get_tag());
    }
}

Vec2<int>
CollisionManager::position_to_grid_cell(const Vec2<float> & position) const
{
    const int cellX = static_cast<int>(position.x) / config::tile::kTileWidth;
    const int cellY = static_cast<int>(position.y) / config::tile::kTileHeight;
    return { cellX, cellY };
}

bool
CollisionManager::is_cell_on_bounds(const Vec2<int> & cell) const
{
    return (cell.x >= 0 && cell.x < static_cast<int>(_grid.size()) &&
            cell.y >= 0 && cell.y < static_cast<int>(_grid[0].size()));
}

Vec2<float>
CollisionManager::get_box_center_position(const CollisionBox & box) const
{
    return { box.get_position().x + (box.size.x / 2.f),
             box.get_position().y + (box.size.y / 2.f) };
}
