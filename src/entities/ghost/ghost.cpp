#include "ghost.h"
#include <iostream>

Ghost::Ghost(InputManager *const inputManager, Entities *entitiesRegistry)
  : m_inputManager(inputManager)
  , m_entitiesRegistry(entitiesRegistry)
{
}

void
Ghost::update()
{
}

void
Ghost::render(SDL_Renderer *renderer) const
{
}
