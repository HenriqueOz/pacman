#include "pacman.h"

#include <iostream>

Pacman::Pacman(InputManager *const inputManager)
  : Entity(inputManager)
{
}

void
Pacman::update()
{
    if (m_inputManager->isKeyReleased(SDLK_D)) {
        std::cout << "VAGABUNDO SOLTOU D"
                  << "\n";
    }
}

void
Pacman::render(SDL_Renderer *renderer) const
{
    SDL_FRect fillRect = { 0, 0, 30, 30 };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &fillRect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
