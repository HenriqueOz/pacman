#include "input.hpp"
#include "SDL3/SDL_log.h"

Input::Input(std::unordered_map<SDL_Keycode, Key> & keyStates)
  : _keyStates(keyStates)
{
}

bool
Input::key_pressed(SDL_Keycode key) const
{
    const auto it = _keyStates.find(key);
    return it != _keyStates.end() && it->second.pressed;
}

bool
Input::key_released(SDL_Keycode key) const
{
    const auto it = _keyStates.find(key);
    return it != _keyStates.end() && it->second.released;
}
