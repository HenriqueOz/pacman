#include "game_controller.h"
#include "config/config.h"
#include "entities/pacman/pacman.h"
#include "entities/utils/utils.h"
#include "vec/vec.h"
#include <SDL3/SDL_stdinc.h>

GameController::GameController(Entities *entitiesRegistry)
  : m_entitiesRegistry(entitiesRegistry)
{
}

bool
GameController::pacmanExists() const
{
    return getPacman() != nullptr;
}

Vec2
GameController::getPacmanPosition() const
{
    return getPacman()->getPosition();
}

Pacman *
GameController::getPacman() const
{
    return static_cast<Pacman *>(m_entitiesRegistry->getEntityById(m_pacmanId));
}

void
GameController::registerPacmanId(Uint32 pacmanId)
{
    if (m_pacmanId == 0) {
        m_pacmanId = pacmanId;
    }
}

void
GameController::registerGhostDoorId(Uint32 ghostDoorId)
{
    if (m_ghostDoorId == 0) {
        m_ghostDoorId = ghostDoorId;
    }
}

Vec2
GameController::getGhostDoorExitPosition() const
{
    const auto ghostDoor = m_entitiesRegistry->getEntityById(m_ghostDoorId);
    if (ghostDoor == nullptr) {
        return Vec2{ 0, 0 };
    }

    const Vec2 ghostDoorPosition = ghostDoor->getPosition();

    return Vec2(ghostDoorPosition.x + Config::tileWidth - 1,
                ghostDoorPosition.y - Config::tileHeight);
}

Utils::Direction
GameController::getPacmanFacingDirection() const
{
    return getPacman()->getFacingDirection();
}
