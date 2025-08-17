#ifndef FOOD_H_
#define FOOD_H_

#include "entities/entity.h"

class Food : public Entity
{
  public:
    Food(Vec2 const &pos, bool isSuper);
    ~Food() override {};

    void update() override;
    void render(SDL_Renderer *renderer, TTF_TextEngine *textEngine) const override;
    EntityType getType() const override { return EntityType::FOOD; };

    bool isSuper() const;

  private:
    const bool m_isSuper;
};

#endif
