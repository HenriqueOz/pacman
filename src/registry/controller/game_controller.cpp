#include "game_controller.h"
#include "config/config.h"
#include "registry/registry.h"
#include "vec/vec.h"
#include <SDL3/SDL_stdinc.h>

GameController::GameController()
{
    m_entitiesRegistry = Registry::getEntitiesRegistry();
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

Entity *
GameController::getPacman() const
{
    return m_entitiesRegistry->getEntityById(m_pacmanId);
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

    return Vec2(ghostDoorPosition.x, ghostDoorPosition.y - Config::tileHeight);
}
