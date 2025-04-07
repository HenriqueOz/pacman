#ifndef VEC_H_
#define VEC_H_

struct Vec2
{
    float x;
    float y;

    void update(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
    void updateX(float x) { this->x = x; }
    void updateY(float y) { this->y = y; }
};

#endif