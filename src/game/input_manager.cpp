#include "input_manager.hpp"
#include "SDL3/SDL_keycode.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_oldnames.h>
#include <unordered_map>

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

bool
InputManager::key_pressed(SDL_Keycode key) const
{
    const auto it = _keyStates.find(key);
    return it != _keyStates.end() && it->second.pressed;
}

bool
InputManager::key_released(SDL_Keycode key) const
{
    const auto it = _keyStates.find(key);
    return it != _keyStates.end() && it->second.released;
}
