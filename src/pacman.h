#ifndef _PACMAN_H
#define _PACMAN_H

#include "entity.h"

class Pacman : public Entity
{

  public:
    Pacman(InputManager *const inputManager);
    ~Pacman() override{};

    void update() override;
    void render(SDL_Renderer *renderer) const override;
};

#endif