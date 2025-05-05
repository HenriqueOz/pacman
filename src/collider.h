#ifndef COLLIDER_H_
#define COLLIDER_H_

#include "entity.h"
#include "input_manager.h"
#include "vec.h"

class Collider : public Entity
{
  public:
    Collider(const Vec2 &position);
    ~Collider(){};

    void update() override;
    void render(SDL_Renderer *renderer) const override;
    EntityType getType() const override { return COLLIDER; };
};

#endif