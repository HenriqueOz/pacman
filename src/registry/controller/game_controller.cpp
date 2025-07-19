#include "game_controller.h"
#include "entities/pacman/pacman.h"

GameController::GameController(Pacman *pacman)
  : m_pacman(pacman)
{
}

bool
GameController::pacmanExists() const
{
    return m_pacman != nullptr;
}

Vec2
GameController::getPacmanPosition() const
{
    return m_pacman->getPosition();
}
