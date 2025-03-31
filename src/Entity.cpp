#include "entity.h"

void
Entity::render(SDL_Renderer *renderer) const
{
}

Entity::Entity(InputManager *const inputManager)
  : m_inputManager(inputManager)
{
}
