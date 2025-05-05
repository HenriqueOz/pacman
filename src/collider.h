#ifndef COLLIDER_H_
#define COLLIDER_H_

#include "entity.h"
#include "input_manager.h"
#include "vec.h"

class Collider : public Entity
{
  public:
    Collider(const Vec2 &position)
      : Entity()
      , m_position(position){};
    ~Collider(){};

    void update() override;
    void render(SDL_Renderer *renderer) const override;
    EntityType getType() const override { return COLLIDER; };

  private:
    Vec2 m_position;
};

#endif