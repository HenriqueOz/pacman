#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <unordered_map>

#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>

struct Key
{
    SDL_Keycode code;
    bool pressed;
    bool released;
};

class InputManager
{
  public:
    InputManager(std::unordered_map<SDL_Keycode, Key> & keyStates);
    ~InputManager() = default;

    void process_input(SDL_Event & event);

  private:
    SDL_Keycode _releasedKeyCode = 0;
    std::unordered_map<SDL_Keycode, Key> & _keyStates;
    bool _keyReleased = false;
};

#endif
