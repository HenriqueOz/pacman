#ifndef INPUT_H_
#define INPUT_H_

#include <unordered_map>

#include "SDL3/SDL_keycode.h"

#include "game/input_manager.hpp"

class Input
{
  public:
    Input(std::unordered_map<SDL_Keycode, Key> & keyStates);
    ~Input() = default;

    bool key_pressed(SDL_Keycode key) const;
    bool key_released(SDL_Keycode key) const;

  private:
    std::unordered_map<SDL_Keycode, Key> & _keyStates;
};

#endif