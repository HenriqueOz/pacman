#include <game/controller/game_controller.hpp>
#include <config/config.hpp>
#include <entities/pacman/pacman.hpp>
#include <entities/utils/movement.hpp>
#include <vec/vec.hpp>
#include <SDL3/SDL_stdinc.h>

GameController::GameController(Entities * entitiesRegistry)
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

void
GameController::addFoodScore()
{
    m_score += 10;
}

void
GameController::addSuperFoodScore()
{
    m_score += 50;
}

void
GameController::resetScore()
{
    m_score = 0;
}

void
GameController::removePacmanLife()
{
    if (m_pacmanLifes > 0) {
        --m_pacmanLifes;
    }
}

void
GameController::addPacmanLife()
{
    ++m_pacmanLifes;
}

void
GameController::resetPacmanLifes()
{
    m_pacmanLifes = m_PACMAN_INITIAL_LIFES;
}

unsigned int
GameController::getPacmanLifes() const
{
    return m_pacmanLifes;
}

unsigned int
GameController::getScore() const
{
    return m_score;
}
