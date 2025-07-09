#ifndef _GAME_H
#define _GAME_H

#include "window/window.h"
#include <SDL3/SDL.h>
#include <cstddef>
#include <registry/entities/entities.h>
#include <registry/input/input_manager.h>
#include <string>

class Game
{
  public:
    Game();
    ~Game() {};

    bool isRunning() const;

    void handleInput(InputManager *inputManager);

    void init(Window &window);
    void render(Entities *entities);
    void update(Entities *entities);
    void clean();
    void closeGame();
    void run(Window &windows, InputManager *inputManager, Entities *entitiesRegistry);

  private:
    std::string m_windowName;
    std::size_t m_windowWidth;
    std::size_t m_windowHeight;

    SDL_Renderer *m_renderer;

    bool m_isRunning;
};

#endif