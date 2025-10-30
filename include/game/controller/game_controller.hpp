#ifndef PACMAN_GAME_CONTROLLER_HPP_
#define PACMAN_GAME_CONTROLLER_HPP_

#include "entities/utils/movement.hpp"
#include "game/entities/entities.hpp"
#include "vec/vec.hpp"
#include <SDL3/SDL_stdinc.h>

class GameController
{
  public:
    GameController(Entities * entitiesRegistry);
    ~GameController() {}

    void registerPacmanId(Uint32 pacmanId);
    void registerGhostDoorId(Uint32 ghostDoorId);
    void registerBlinkyId(Uint32 blinky);

    bool pacmanExists() const;
    Vec2 getPacmanPosition() const;
    Utils::Direction getPacmanFacingDirection() const;

    Vec2 getGhostDoorExitPosition() const;
    Vec2 getBlinkyPosition() const;

    void addFoodScore();
    void addSuperFoodScore();
    void resetScore();
    unsigned int getScore() const;

    void removePacmanLife();
    void addPacmanLife();
    void resetPacmanLifes();
    unsigned int getPacmanLifes() const;

  private:
    const unsigned int m_PACMAN_INITIAL_LIFES = 3;
    unsigned int m_pacmanLifes = m_PACMAN_INITIAL_LIFES;

    unsigned int m_score = 0;

    Vec2 getEntitytPositionById(Uint32 id) const;

    Uint32 m_pacmanId = 0;
    Uint32 m_ghostDoorId = 0;
    Uint32 m_blinkyId = 0;

    Entities * m_entitiesRegistry;
};

#endif
