#include "pacman.h"

#include <iostream>

Pacman::Pacman(InputManager *const inputManager)
  : Entity(inputManager)
{
}

void
Pacman::update()
{
    // if (m_inputManager->isKeyPressed(SDLK_D)) {
    //     std::cout << "VAGABUNDO APERTOU D"
    //               << "\n";
    // }

    if (m_inputManager->isKeyReleased(SDLK_D)) {
        std::cout << "VAGABUNDO SOLTOU D"
                  << "\n";
    }
}