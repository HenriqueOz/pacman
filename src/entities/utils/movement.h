#ifndef UTILS_H_
#define UTILS_H_

#include "config/config.h"
#include "vec/vec.h"
#include <cmath>
#include <cstdlib>

namespace Utils {

enum class Direction : int
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UNDEFINED,
};

inline Vec2
positionToTiles(Vec2 const &pos)
{
    return { static_cast<int>(pos.x / Config::tileWidth),
             static_cast<int>(pos.y / Config::tileHeight) };
}

inline Vec2
tilesToPosition(Vec2 const &pos)
{
    return {
        static_cast<int>(pos.x * Config::tileWidth),
        static_cast<int>(pos.y * Config::tileHeight),
    };
}

inline int
getDirectionValue(Utils::Direction direction)
{
    switch (direction) {
        case Utils::Direction::LEFT:
        case Utils::Direction::UP:
            return -1;
        case Utils::Direction::RIGHT:
        case Utils::Direction::DOWN:
            return 1;
        default:
            return 0;
    }
}

inline Utils::Direction
getReverseDirection(Utils::Direction direction)
{
    return static_cast<Utils::Direction>((static_cast<int>(direction) + 2) % 3);
}

inline Vec2
getNextTilePositionAt(Vec2 position, Utils::Direction direction)
{
    const Vec2 tile = positionToTiles(position);

    switch (direction) {
        case Utils::Direction::UP:
            return Utils::tilesToPosition(Vec2(tile.x, tile.y - 1));
        case Utils::Direction::DOWN:
            return Utils::tilesToPosition(Vec2(tile.x, tile.y + 1));
        case Utils::Direction::LEFT:
            return Utils::tilesToPosition(Vec2(tile.x - 1, tile.y));
        case Utils::Direction::RIGHT:
            return Utils::tilesToPosition(Vec2(tile.x + 1, tile.y));
    }

    return Vec2(0, 0);
}

inline float
getDotsDistance(Vec2 a, Vec2 b)
{
    return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
}

inline float
getManhattanDistance(Vec2 a, Vec2 b)
{
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}
};

#endif