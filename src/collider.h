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

  private:
    Vec2 m_position;
    Vec2 m_size;
};

#endif