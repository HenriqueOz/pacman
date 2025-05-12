#include "collider.h"

Collider::Collider(const Vec2 &position, const Vec2 &size)
  : Entity()
{
    m_position.update(position);
    m_size.update(size);
}

void
Collider::update()
{
}

void
Collider::render(SDL_Renderer *renderer) const
{
    SDL_FRect rect = { static_cast<float>(m_position.x),
                       static_cast<float>(m_position.y),
                       static_cast<float>(m_size.x),
                       static_cast<float>(m_size.y) };

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
