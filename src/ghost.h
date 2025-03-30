#ifndef _GHOST_H
#define _GHOST_H

#include "entity.h"

class Ghost : public Entity
{

  public:
    void update() override;
};

#endif