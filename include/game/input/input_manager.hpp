#ifndef INPUT_MANAGER_HPP_
#define INPUT_MANAGER_HPP_

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <unordered_map>

class InputManager
{
  public:
    void processInput(SDL_Event & event);
    bool isKeyPressed(SDL_Keycode key) const;
    bool isKeyReleased(SDL_Keycode key) const;

  private:
    std::unordered_map<SDL_Keycode, bool> keyPacmanStates;
    std::unordered_map<SDL_Keycode, bool> releasedKeys;
    bool m_releaseKeyPressed = false;
    SDL_Keycode m_releasedKey;
};

#endif
