#include "ghost.h"
#include "config/config.h"

Ghost::Ghost(Vec2 const &pos)
{
    m_position.update(pos);
    m_size.update(Config::tileWidth, Config::tileHeight);
    m_state = GhostStates::Idle;
}

void
Ghost::update()
{
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
}
