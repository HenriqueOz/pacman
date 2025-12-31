#include <algorithm>
#include <unordered_set>
#include <vector>

#include "collision_manager.hpp"

CollisionManager::CollisionManager(CollisionGrid & grid)
  : _grid(grid)
{
}

void
CollisionManager::register_box(const CollisionBox * box)
{
    const std::vector<Vec2<int>> cells = get_cells_within(box->position, box->size);

    for (const Vec2<int> & cell : cells) {
        if (is_cell_on_bounds(cell)) {
            get_cell(cell).push_back(box);
        }
    }
}

void
CollisionManager::unregister_box(const CollisionBox * box)
{
    auto it = _boxCells.find(box);
    if (it == _boxCells.end())
        return;

    for (const Vec2<int> & cell : it->second) {
        if (is_cell_on_bounds(cell)) {
            GridCell & cellBoxes = get_cell(cell);
            cellBoxes.erase(std::remove(cellBoxes.begin(), cellBoxes.end(), box), cellBoxes.end());
        }
    }

    _boxCells.erase(it);
}

bool
CollisionManager::check_collision_at(const Vec2<float> & position, const Vec2<int> & size, CollisionTag tag) const
{
    const std::vector<Vec2<int>> cells = get_cells_within(position, size);

    for (const Vec2<int> & cell : cells) {
        if (!is_cell_on_bounds(cell))
            continue;

        const GridCell & gridCell = get_cell(cell);
        for (const CollisionBox * box : gridCell) {
            if (box->tag == tag) {
                if (aabb_check(position, size, box->position, box->size)) {
                    return true;
                }
            }
        }
    }

    return false;
}

std::vector<const CollisionBox *>
CollisionManager::get_collisions_at(const Vec2<float> & position, const Vec2<int> & size) const
{

    std::vector<const CollisionBox *> result;
    std::unordered_set<const CollisionBox *> visited;

    const std::vector<Vec2<int>> cells = get_cells_within(position, size);

    for (const Vec2<int> & cell : cells) {
        if (!is_cell_on_bounds(cell))
            continue;

        const GridCell & gridCell = get_cell(cell);
        for (const CollisionBox * box : gridCell) {
            if (visited.count(box))
                continue;
            visited.insert(box);

            const Vec2<float> boxPosition = box->position;
            if (position.x < (boxPosition.x + box->size.x) && (position.x + size.x) > boxPosition.x &&
                position.y < (boxPosition.y + box->size.y) && (position.y + size.y) > boxPosition.y) {
                result.push_back(box);
            }
        }
    }

    return result;
}

void
CollisionManager::update_box_position(CollisionBox * box, const Vec2<float> & newPos)
{
    std::vector<Vec2<int>> oldCells = get_cells_within(box->position, box->size);
    std::vector<Vec2<int>> newCells = get_cells_within(newPos, box->size);

    for (const Vec2<int> & cell : oldCells) {
        if (is_cell_on_bounds(cell)) {
            GridCell & cellBoxes = get_cell(cell);
            cellBoxes.erase(std::remove(cellBoxes.begin(), cellBoxes.end(), box), cellBoxes.end());
        }
    }

    for (const Vec2<int> & cell : newCells) {
        if (is_cell_on_bounds(cell)) {
            get_cell(cell).push_back(box);
        }
    }

    _boxCells[box] = newCells;
    box->position = newPos;
}

std::vector<Vec2<int>>
CollisionManager::get_cells_within(const Vec2<float> & position, const Vec2<int> & size) const
{
    std::vector<Vec2<int>> cells;

    const Vec2<int> topLeft = position_to_grid_cell(position);
    const Vec2<int> bottomRight = position_to_grid_cell({ position.x + size.x - 1, position.y + size.y - 1 });

    for (int x = topLeft.x; x <= bottomRight.x; x++) {
        for (int y = topLeft.y; y <= bottomRight.y; y++) {
            cells.push_back({ x, y });
        }
    }

    return cells;
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
    return (cell.x >= 0 && cell.x < static_cast<int>(_grid.size()) && cell.y >= 0 &&
            cell.y < static_cast<int>(_grid[0].size()));
}

bool
CollisionManager::aabb_check(const Vec2<float> & p1,
                             const Vec2<int> & s1,
                             const Vec2<float> & p2,
                             const Vec2<int> & s2) const
{
    return (p1.x < (p2.x + s2.x) && (p1.x + s1.x) > p2.x && p1.y < (p2.y + s2.y) && (p1.y + s1.y) > p2.y);
}
