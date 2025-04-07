#include "input_manager.h"

void
InputManager::processInput()
{
    if (m_releaseKeyPressed) {
        releasedKeys[m_releasedKey] = false;
        m_releaseKeyPressed = false;
    }

    SDL_Event event;
    while (SDL_PollEvent(&event)) {

        switch (event.type) {
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                m_quitRequested = true;
                break;
            case SDL_EVENT_KEY_DOWN:
                if (!event.key.repeat) {
                    keyPacmanStates[event.key.key] = true;
                }
                break;
            case SDL_EVENT_KEY_UP:
                if (keyPacmanStates[event.key.key]) {
                    m_releasedKey = event.key.key;
                    m_releaseKeyPressed = true;
                    releasedKeys[m_releasedKey] = true;
                }
                keyPacmanStates[event.key.key] = false;
                break;
        }
    }
}

bool
InputManager::isKeyPressed(SDL_Keycode key)
{
    auto it = keyPacmanStates.find(key);
    return it != keyPacmanStates.end() && it->second;
}

bool
InputManager::isKeyReleased(SDL_Keycode key)
{
    auto it = releasedKeys.find(key);
    return it != releasedKeys.end() && it->second;
}

bool
InputManager::quitRequested() const
{
    return m_quitRequested;
}
