#include "game_controller.h"
#include "config/config.h"
#include "entities/pacman/pacman.h"
#include "entities/utils/movement.h"
#include "vec/vec.h"
#include <SDL3/SDL_stdinc.h>

GameController::GameController(Entities *entitiesRegistry)
  : m_entitiesRegistry(entitiesRegistry)
{
}

bool
GameController::pacmanExists() const
{
    return m_pacmanId != 0 && m_entitiesRegistry->getEntityById(m_pacmanId);
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

void
GameController::registerBlinkyId(Uint32 blinkyId)
{
    if (m_blinkyId == 0) {
        m_blinkyId = blinkyId;
    }
}

Vec2
GameController::getGhostDoorExitPosition() const
{
    const Vec2 ghostDoor = getEntitytPositionById(m_ghostDoorId);
    return Vec2(ghostDoor.x + Config::tileWidth - 1, ghostDoor.y - Config::tileHeight);
}

Utils::Direction
GameController::getPacmanFacingDirection() const
{
    const auto pacman = static_cast<Pacman *>(m_entitiesRegistry->getEntityById(m_pacmanId));
    if (pacman) {
        return pacman->getFacingDirection();
    }
    return Utils::Direction::UNDEFINED;
}

Vec2
GameController::getEntitytPositionById(Uint32 id) const
{
    const auto entity = m_entitiesRegistry->getEntityById(id);
    if (!entity) {
        return { 0, 0 };
    }
    return entity->getPosition();
}

Vec2
GameController::getPacmanPosition() const
{
    return getEntitytPositionById(m_pacmanId);
}

Vec2
GameController::getBlinkyPosition() const
{
    return getEntitytPositionById(m_blinkyId);
}