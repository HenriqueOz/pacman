#ifndef VEC_H_
#define VEC_H_

#include <functional>

struct Vec2
{
    int x, y;

    Vec2(int _x, int _y)
      : x(_x)
      , y(_y){};

    /**
     * * @brief Update the vector with new x and y values.
     * @param _x The new x value.
     * @param _y The new y value.
     */
    inline void update(int _x, int _y)
    {
        this->x = _x;
        this->y = _y;
    }
    /**
     * @brief Update the vector with a single value.
     * @param _x The value to set both x and y to.
     */
    inline void update(int _x)
    {
        this->x = _x;
        this->y = _x;
    }
    /**
     * @brief Update the vector with another vector.
     * @param v The vector to copy values from.
     */
    inline void update(Vec2 const &v)
    {
        this->x = v.x;
        this->y = v.y;
    }

    inline bool equals(Vec2 const &v) const { return this->x == v.x && this->y == v.y; }
};

#endif