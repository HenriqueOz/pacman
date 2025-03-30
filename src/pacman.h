#ifndef _PACMAN_H
#define _PACMAN_H

#include "entity.h"

class Pacman : public Entity
{

  public:
    void update() override;
};

#endif