#ifndef PACMAN_REGISTRY_H_
#define PACMAN_REGISTRY_H_

#include "entities/pacman/pacman.h"
#include "vec/vec.h"

class GameController
{
  public:
    GameController(Pacman *pacman);
    ~GameController() {}

    bool pacmanExists() const;
    Vec2 getPacmanPosition() const;

  private:
    Pacman *m_pacman = nullptr;
};

#endif