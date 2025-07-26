#ifndef _GAME_H
#define _GAME_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <game/controller/game_controller.h>
#include <game/entities/entities.h>
#include <game/input/input_manager.h>

class Game
{
  public:
    Game(InputManager *inputManager, Entities *entities, GameController *gameController);
    ~Game() {};

    bool isRunning() const;
    void init();
    void render();
    void update();
    void clean();
    void closeGame();
    void run();

  private:
    void handleInput();

    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    bool m_isRunning;

    InputManager *m_inputManager;
    Entities *m_entities;
    GameController *m_gameController;
};

#endif