#ifndef VEC_H_
#define VEC_H_

struct Vec2
{
    int x, y;

    Vec2(int _x, int _y)
      : x(_x)
      , y(_y) {};

    inline void update(int _x, int _y)
    {
        this->x = _x;
        this->y = _y;
    }

    inline void update(int _x)
    {
        this->x = _x;
        this->y = _x;
    }

    inline void update(Vec2 const &v)
    {
        this->x = v.x;
        this->y = v.y;
    }

    inline bool equals(Vec2 const &v) const { return this->x == v.x && this->y == v.y; }
};

#endif