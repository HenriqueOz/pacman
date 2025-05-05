#ifndef VEC_H_
#define VEC_H_

#include <functional>

struct Vec2
{
    float x, y;

    Vec2(float _x, float _y)
      : x(_x)
      , y(_y){};

    void update(Vec2 const &v)
    {
        this->x = v.x;
        this->y = v.y;
    }
};

#endif