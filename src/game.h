#ifndef _GAME_H
#define _GAME_H

#include "entities.h"
#include "entity.h"
#include "input_manager.h"
#include "map.h"
#include "window.h"
#include <SDL3/SDL.h>
#include <cstddef>
#include <memory>
#include <string>
#include <vector>


class Game
{
  public:
    inline static Game *getInstance()
    {
        if (m_instance == nullptr)
            m_instance = new Game();
        return m_instance;
    }

    ~Game(){};

    bool isRunning() const;

    void handleInput(InputManager *inputManager);

    void init(Window &window);
    void render(Entities &entities);
    void update(Entities &entities);
    void clean();
    void closeGame();

  private:
    Game();

    static Game *m_instance;

    std::string m_windowName;
    std::size_t m_windowWidth;
    std::size_t m_windowHeight;

    SDL_Renderer *m_renderer;

    bool m_isRunning;
};

#endif