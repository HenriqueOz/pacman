#include "ghost.h"
#include "config/config.h"
#include "registry/controller/game_controller.h"
#include "registry/registry.h"
#include "vec/vec.h"
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>

Ghost::Ghost(Vec2 const &pos)
{
    m_position.update(pos);
    m_size.update(Config::tileWidth, Config::tileHeight);
    m_state = GhostStates::IDLE;
    m_gameController = Registry::getGameController();
}

void
Ghost::update()
{
    if (!m_gameController->pacmanExists()) {
        return;
    }

    switch (m_state) {
        case GhostStates::IDLE:
            exitSpawn();
            break;
        case GhostStates::CHASING:
            moveTo(m_gameController->getPacmanPosition());
            break;
        case GhostStates::ESCAPING:
        case GhostStates::DEAD:
            break;
    }
}

void
Ghost::render(SDL_Renderer *renderer) const
{
    SDL_FRect rect = { static_cast<float>(m_position.x),
                       static_cast<float>(m_position.y),
                       static_cast<float>(m_size.x),
                       static_cast<float>(m_size.y) };

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    if (m_state == GhostStates::IDLE) {
        drawTriangleToTarget(renderer, m_gameController->getGhostDoorExitPosition());
    } else if (m_state == GhostStates::CHASING) {
        drawTriangleToTarget(renderer, m_gameController->getPacmanPosition());
    }
}

void
Ghost::exitSpawn()
{
}

void
Ghost::moveTo(Vec2 position)
{
}

void
Ghost::drawTriangleToTarget(SDL_Renderer *renderer, Vec2 target) const
{
    const Vec2 diff = {
        target.x - m_position.x,
        target.y - m_position.y,
    };

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderLine(renderer, m_position.x, m_position.y, target.x, target.y);
    SDL_RenderLine(renderer, m_position.x, m_position.y, m_position.x + diff.x, m_position.y);
    SDL_RenderLine(
      renderer, m_position.x + diff.x, m_position.y, m_position.x + diff.x, m_position.y + diff.y);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}