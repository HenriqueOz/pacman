#ifndef _GHOST_H
#define _GHOST_H

#include <entities/entity.h>

class Ghost : public Entity
{
  public:
    Ghost();
    ~Ghost() override {};
    EntityType getType() const override { return GHOST; };

    void update() override;
    void render(SDL_Renderer *renderer) const override;

  private:
};

#endif