#ifndef VEC_H_
#define VEC_H_

#include <functional>

struct Vec2
{
    float x, y;

    Vec2() = default;
    Vec2(float _x, float _y)
      : x(_x)
      , y(_y){};

    bool operator==(const Vec2 &other) const { return x == other.x && y == other.y; }

    void update(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
};

namespace std {
template<>
struct hash<Vec2>
{
    std::size_t operator()(const Vec2 &v) const noexcept
    {
        return std::hash<float>()(v.x) ^ (std::hash<float>()(v.y) << 1);
    }
};
}

#endif