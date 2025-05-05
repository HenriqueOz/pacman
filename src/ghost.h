#ifndef _GHOST_H
#define _GHOST_H

#include "entity.h"
#include "input_manager.h"

class Ghost : public Entity
{
  public:
    Ghost(InputManager *const inputManager);
    ~Ghost() override{};
    EntityType getType() const override { return GHOST; };

    void update() override;
    void render(SDL_Renderer *renderer) const override;
};

#endif