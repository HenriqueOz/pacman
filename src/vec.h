#ifndef VEC_H_
#define VEC_H_

#include <functional>

struct Vec2
{
    float x, y;

    Vec2(float _x, float _y)
      : x(_x)
      , y(_y){};

    void update(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
};

#endif