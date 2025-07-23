#ifndef UTILS_H_
#define UTILS_H_

#include "config/config.h"
#include "vec/vec.h"
namespace Utils {

enum class Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UNDEFINED,
};

inline Vec2
fixPositionToGrid(Vec2 const &pos)
{
    return { static_cast<int>(pos.x / Config::tileWidth),
             static_cast<int>(pos.y / Config::tileHeight) };
}

inline Vec2
gridPositionToReal(Vec2 const &pos)
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

};

#endif