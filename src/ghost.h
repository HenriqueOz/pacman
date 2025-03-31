#ifndef _GHOST_H
#define _GHOST_H

#include "entity.h"

class Ghost : public Entity
{

  public:
    Ghost(InputManager *const inputManager);
    ~Ghost() override{};

    void update() override;
    void render(SDL_Renderer *renderer) const override;
};

#endif