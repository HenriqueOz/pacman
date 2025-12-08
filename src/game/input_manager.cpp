#include <unordered_map>

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_oldnames.h>

#include "input_manager.hpp"

InputManager::InputManager(std::unordered_map<SDL_Keycode, Key> & keyStates)
  : _keyStates(keyStates)
{
}

void
InputManager::process_input(SDL_Event & event)
{
    if (_keyStates[_releasedKeyCode].released) {
        _keyStates[_releasedKeyCode].released = false;
    }

    switch (event.type) {
        case SDL_EVENT_KEY_DOWN:
            if (!event.key.repeat) {
                _keyStates[event.key.key].pressed = true;
            }
            break;
        case SDL_EVENT_KEY_UP:
            if (_keyStates[event.key.key].pressed) {
                Key & key = _keyStates[_releasedKeyCode];

                _releasedKeyCode = event.key.key;

                key.released = true;
                key.pressed = false;
            }
            break;
    }
}
