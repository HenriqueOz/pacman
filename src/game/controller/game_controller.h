#ifndef PACMAN_GAME_CONTROLLER_H_
#define PACMAN_GAME_CONTROLLER_H_

#include "entities/utils/movement.h"
#include "game/entities/entities.h"
#include "vec/vec.h"
#include <SDL3/SDL_stdinc.h>

class GameController
{
  public:
    GameController(Entities *entitiesRegistry);
    ~GameController() {}

    void registerPacmanId(Uint32 pacmanId);
    void registerGhostDoorId(Uint32 ghostDoorId);
    void registerBlinkyId(Uint32 blinky);

    bool pacmanExists() const;
    Vec2 getPacmanPosition() const;
    Utils::Direction getPacmanFacingDirection() const;

    Vec2 getGhostDoorExitPosition() const;
    Vec2 getBlinkyPosition() const;

  private:
    Vec2 getEntitytPositionById(Uint32 id) const;

    Uint32 m_pacmanId = 0;
    Uint32 m_ghostDoorId = 0;
    Uint32 m_blinkyId = 0;

    Entities *m_entitiesRegistry;
};

#endif
