#ifndef _GAME_H
#define _GAME_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_ttf/SDL_ttf.h>
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

    SDL_Window *m_window = nullptr;
    SDL_Renderer *m_renderer = nullptr;

    SDL_Texture *m_gameTexture = nullptr;
    SDL_Texture *m_guiTexture = nullptr;

    TTF_TextEngine *m_textEngine = nullptr;

    bool m_isRunning;

    InputManager *m_inputManager = nullptr;
    Entities *m_entities = nullptr;
    GameController *m_gameController = nullptr;
};

#endif
