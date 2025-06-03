#include "pacman.h"
#include "collider.h"
#include "config.h"
#include "game.h"
#include <iostream>

Pacman::Pacman(Vec2 const &pos,
               InputManager *const inputManager,
               Entities *entitiesRegistry = nullptr)
  : m_inputManager(inputManager)
  , m_entitiesRegistry(entitiesRegistry)
  , m_velocity(0.f, 0.f)
  , m_PacmanState(IDLE)
  , m_speed(1)
  , m_dirx(0)
  , m_diry(0)
{
    m_size.update(Config::tileWidth, Config::tileHeight);
    m_position.update(pos);
    m_position.x += m_size.x / 2;
}

void
Pacman::update()
{
    switch (m_PacmanState) {
        case IDLE:
            idle();
            break;
        case MOVING:
            moving();
            break;
        case DEAD:
            break;
    }
}

void
Pacman::render(SDL_Renderer *renderer) const
{
    SDL_FRect rect = { static_cast<float>(m_position.x),
                       static_cast<float>(m_position.y),
                       static_cast<float>(m_size.x),
                       static_cast<float>(m_size.y) };

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void
Pacman::handleInput()
{
    if (m_inputManager->isKeyPressed(m_left)) {
        m_dirx = -1;
        m_diry = 0;
    } else if (m_inputManager->isKeyPressed(m_right)) {
        m_dirx = 1;
        m_diry = 0;
    } else if (m_inputManager->isKeyPressed(m_up)) {
        m_dirx = 0;
        m_diry = -1;
    } else if (m_inputManager->isKeyPressed(m_down)) {
        m_dirx = 0;
        m_diry = 1;
    }
}

void
Pacman::idle()
{
    handleInput();

    if (m_dirx != 0 || m_diry != 0) {
        m_PacmanState = MOVING;
    }
}

void
Pacman::moving()
{
    int pastDirX = m_dirx;
    int pastDirY = m_diry;
    m_velocity.update(static_cast<float>(m_speed));

    handleInput();
    horizontalMovement(pastDirX, pastDirY);
    verticalMovement(pastDirX, pastDirY);
    wrapOutOfBounds();

    m_position.x += m_dirx * m_velocity.x;
    m_position.y += m_diry * m_velocity.y;
}

void
Pacman::horizontalMovement(int pastDirX, int pastDirY)
{
    if (m_dirx == 0)
        return;

    int x;
    if (m_dirx > 0) {
        x = m_position.x + m_size.x - 1;
    } else {
        x = m_position.x;
    }

    const bool collisionTopX =
      m_entitiesRegistry->hasEntityAt<EntityType::COLLIDER>(x + m_dirx, m_position.y);
    const bool collisionBottomX = m_entitiesRegistry->hasEntityAt<EntityType::COLLIDER>(
      x + m_dirx, m_position.y + m_size.y - 1);

    if (collisionTopX || collisionBottomX) {
        m_dirx = 0;
        m_diry = pastDirY;
    }
}

void
Pacman::verticalMovement(int pastDirX, int pastDirY)
{
    if (!m_diry)
        return;

    int y;
    if (m_diry > 0) {
        y = m_position.y + m_size.y - 1;
    } else {
        y = m_position.y;
    }

    const bool collisionLeft =
      m_entitiesRegistry->hasEntityAt<EntityType::COLLIDER>(m_position.x, y + m_diry);
    const bool collisionRight = m_entitiesRegistry->hasEntityAt<EntityType::COLLIDER>(
      m_position.x + m_size.x - 1, y + m_diry);

    if (collisionLeft || collisionRight) {
        m_dirx = pastDirX;
        m_diry = 0;
    }
}

void
Pacman::wrapOutOfBounds()
{
    const std::size_t width = Config::logicalWidth;
    const std::size_t height = Config::logicalHeight;
    const std::size_t pacmanWidth = m_size.x;
    const std::size_t pacmanHeight = m_size.y;

    if (m_position.x < 0) {
        m_position.x = width - pacmanWidth;
    } else if (m_position.x > width) {
        m_position.x = 0;
    } else if (m_position.y < 0) {
        m_position.y = height - pacmanHeight;
    } else if (m_position.y > height) {
        m_position.y = 0;
    }
}
