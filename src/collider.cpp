#include "collider.h"

Collider::Collider(const Vec2 &position)
{
    m_position.update(position);
}

void
Collider::update()
{
}

void
Collider::render(SDL_Renderer *renderer) const
{
}
