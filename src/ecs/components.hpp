#ifndef COMPONENTS_H_
#define COMPONENTS_H_

namespace ecs {
struct Position
{
    float x{};
    float y{};
};

struct Velocity
{
    float value{};
};

struct DirectionControl
{
    int x{};
    int y{};
};

struct Sprite
{
    float x{};
    float y{};
    int width{};
    int height{};
};
}

#endif