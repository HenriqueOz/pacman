#ifndef COLLIDER_H_
#define COLLIDER_H_

#include <entities/entity.h>

class Collider : public Entity
{
  public:
    Collider(const Vec2 &position, const Vec2 &size, bool isGhostDoor);
    ~Collider(){};

    void update() override;
    void render(SDL_Renderer *renderer, TTF_TextEngine *textEngine) const override;
    bool isGhostDoor() const;
    EntityType getType() const override { return COLLIDER; };

  private:
    bool m_isGhostDoor;
};

#endif
