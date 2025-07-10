#ifndef _GAME_H
#define _GAME_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <registry/entities/entities.h>
#include <registry/input/input_manager.h>

class Game
{
  public:
    Game();
    ~Game() {};

    bool isRunning() const;

    void handleInput(InputManager *inputManager);

    void init();
    void render(Entities *entities);
    void update(Entities *entities);
    void clean();
    void closeGame();
    void run(InputManager *inputManager, Entities *entitiesRegistry);

  private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;

    bool m_isRunning;
};

#endif