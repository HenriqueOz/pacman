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
}
