#include "input_manager.h"

void
InputManager::processInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                m_quitRequested = true;
                break;
            default:
        }
    }
}

bool
InputManager::quitRequested() const
{
    return m_quitRequested;
}
