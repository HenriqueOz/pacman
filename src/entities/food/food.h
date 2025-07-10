#ifndef FOOD_H_
#define FOOD_H_

#include "entities/entity.h"

class Food : public Entity
{
  public:
    Food(Vec2 const &pos);
    ~Food() override {};

    void update() override;
    void render(SDL_Renderer *renderer) const override;
    EntityType getType() const override { return EntityType::FOOD; };
};

#endif