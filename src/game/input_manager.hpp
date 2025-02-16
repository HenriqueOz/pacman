#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <unordered_map>

struct Key
{
    SDL_Keycode code;
    bool pressed;
    bool released;
};

class InputManager
{
  public:
    void process_input(SDL_Event & event);
    bool key_pressed(SDL_Keycode key) const;
    bool key_released(SDL_Keycode key) const;

  private:
    std::unordered_map<SDL_Keycode, Key> _keyStates = {};
    bool _keyReleased = false;
    SDL_Keycode _releasedKeyCode = 0;
};

#endif
