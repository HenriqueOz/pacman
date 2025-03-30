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
            case SDL_EVENT_KEY_DOWN:
                if (!event.key.repeat) {
                    keyStates[event.key.key] = true;
                }
                break;
            case SDL_EVENT_KEY_UP:
                keyStates[event.key.key] = false;
                break;
        }
    }
}

bool
InputManager::isKeyPressed(SDL_Keycode key)
{
    std::unordered_map<SDL_Keycode, bool>::iterator it = keyStates.find(key);
    return it != keyStates.end() && it->second;
}

bool
InputManager::quitRequested() const
{
    return m_quitRequested;
}
