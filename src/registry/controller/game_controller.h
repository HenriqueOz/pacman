#ifndef PACMAN_REGISTRY_H_
#define PACMAN_REGISTRY_H_

#include "entities/pacman/pacman.h"
#include "entities/utils/utils.h"
#include "registry/entities/entities.h"
#include "vec/vec.h"
#include <SDL3/SDL_stdinc.h>

class GameController
{
  public:
    GameController();
    ~GameController() {}

    void registerPacmanId(Uint32 pacmanId);
    void registerGhostDoorId(Uint32 ghostDoorId);

    bool pacmanExists() const;
    Vec2 getPacmanPosition() const;
    Vec2 getGhostDoorExitPosition() const;
    Utils::Direction getPacmanDirection() const;

  private:
    Pacman *getPacman() const;

    Uint32 m_pacmanId = 0;
    Uint32 m_ghostDoorId = 0;
    Entities *m_entitiesRegistry;
};

#endif