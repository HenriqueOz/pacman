#include "pacman.h"
#include "game.h"
#include <iostream>

Pacman::Pacman(InputManager *const inputManager)
  : Entity(inputManager)
{
    m_position.update(0.f, 0.f);
    m_velocity.update(0.f, 0.f);
    m_dirx = 0;
    m_diry = 0;
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
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_FRect rect = { m_position.x, m_position.y, 20, 20 };
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
    m_velocity.update(m_speed, m_speed);

    handleInput();

    m_position.x += m_velocity.x * m_dirx;
    m_position.y += m_velocity.y * m_diry;

    wrapOutOfBounds();
}

void
Pacman::wrapOutOfBounds()
{
    const auto width = Game::getInstance()->getWindow()->getWidth();
    const auto height = Game::getInstance()->getWindow()->getHeight();

    if (m_position.x < 0) {
        m_position.x = width - 20;
    } else if (m_position.x > width) {
        m_position.x = 0;
    } else if (m_position.y < 0) {
        m_position.y = height - 20;
    } else if (m_position.y > height) {
        m_position.y = 0;
    }
}
