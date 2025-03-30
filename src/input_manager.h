#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

#include <SDL3/SDL.h>
#include <unordered_map>

class InputManager
{
  public:
    void processInput();
    void isKeyPressed(SDL_Keycode key);
    void isKeyReleased(SDL_Keycode key);
    bool quitRequested() const;

  private:
    std::unordered_map<SDL_Keycode, bool> keyStates;
    bool m_quitRequested = false;
};

#endif